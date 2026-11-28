#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""tsearch.py - a beam search over rewrites of a near miss that keep its meaning (meaning_rewrites.py), judged in process (scorer.py).

  .venv/bin/python scripts/matching/tsearch.py 0x13A688 [SOURCE] [--beam 6] [--depth 4] [--budget 300] [--minutes 20] [--jobs 8]
                                             [--only NAME,...] [--with-neighborhood] [--resume]
  .venv/bin/python scripts/matching/tsearch.py --batch [--min-score 5] [--max-score 16] [--addresses FILE] [same options]

neighborhood.py tries every rewrite of mutate.py and rules.py; this one tries the rewrites of meaning_rewrites.py (statement order by
dependence, loop and conditional forms, switch against if chains, declarations, locals named and merged, pointer walks, ...), each of
which keeps what the function computes. From the start source it judges every single rewrite (kinds interleaved, so a small budget still
tries each kind), keeps the best few (`--beam`, distinct rewrite kinds first among equal scores, worse ones too when nothing is better:
a plateau or a worse step can lead to 0) and rewrites those again, `--depth` times, until score 0, the compile budget or the minutes run
out. A source the scorer judged before costs no compile (work/matching/scorecache/).

Nothing is written to src/, nonmatching/ or data/: everything goes to work/matching/tsearch/<ADDRESS>/:
  log.tsv              depth, score, whether it was compiled (or a cache hit), and the chain of rewrites of every candidate judged
  best_NN.cpp          each improvement (header: score, start score, chain), and best_NN.diff: every step of its chain as a diff, the
                       check_source.py findings of the source, for review before anything is adopted
  zero.cpp, zero.diff  a score of 0: a lead, not a match, until `make land` passes with it in data/matching/src/fn
  state.json           the beam, the sources seen and the compiles used: `--resume` continues where a run stopped
Every improvement and zero is also logged in work/matching/runs.log (arm `tsearch`), as try.py logs a run.

Every candidate must add no finding to the start source (search_guard.py: no banned construct, cleanup problem or review warning) and
none of the constructs meaning_rewrites.forbidden() refuses (asm, register, volatile, a run-once loop, a self-assignment). Walled, blocked
and boundary-suspect functions are skipped (search_guard.skipped; SEARCH_INCLUDE_WALLS=1 searches walls)."""
import argparse
import concurrent.futures
import csv
import hashlib
import importlib
import json
import os
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import meaning_rewrites  # noqa: E402
import scorer  # noqa: E402
import search_guard  # noqa: E402
from progress import Progress  # noqa: E402

LAB = scorer.LAB
SOURCES = os.path.join(LAB, 'data', 'matching', 'src', 'fn')
MANIFEST = os.path.join(LAB, 'nonmatching', 'MANIFEST.tsv')
OUTPUT = os.path.join(LAB, 'work', 'matching', 'tsearch')


class Candidate:
    """A source in the search: its text, the rewrite that made it from its parent, its score; `steps` is the chain as (label, diff)."""
    __slots__ = ('text', 'label', 'parent', 'score', 'stored_steps')

    def __init__(self, text, label=None, parent=None, score=None, stored_steps=None):
        self.text, self.label, self.parent, self.score, self.stored_steps = text, label, parent, score, stored_steps

    def steps(self):
        if self.stored_steps is not None:
            return list(self.stored_steps)
        if self.parent is None:
            return []
        return self.parent.steps() + [(self.label, meaning_rewrites.diff(self.parent.text, self.text))]

    def chain(self):
        return [label for label, _ in self.steps()]


def digest(text):
    return hashlib.sha1(meaning_rewrites.normalized(text).encode()).hexdigest()[:16]


def language_of(path):
    return 'c' if path.endswith('.c') else 'c++'


def source_path(address):
    """The function's source: data/matching/src/fn/<ADDRESS>.cpp (or .c), else its nonmatching/ file."""
    for extension in ('.cpp', '.c'):
        path = os.path.join(SOURCES, f'{address:06X}{extension}')
        if os.path.exists(path):
            return path
    if os.path.exists(MANIFEST):
        with open(MANIFEST, encoding='utf-8') as handle:
            for row in csv.DictReader(handle, delimiter='\t'):
                if int(row['address'], 16) == address:
                    return os.path.join(LAB, 'nonmatching', row['file'])
    return None


def interleaved(candidates):
    """Candidates ordered round-robin over their rewrite kinds, so that a budget smaller than the pool still tries every kind."""
    by_kind = {}
    for candidate in candidates:
        by_kind.setdefault(candidate.label.split('@')[0], []).append(candidate)
    ordered = []
    queues = list(by_kind.values())
    while queues:
        for queue in list(queues):
            ordered.append(queue.pop(0))
            if not queue:
                queues.remove(queue)
    return ordered


def next_beam(judged, width):
    """The best `width` candidates by score, the shorter chain first; among equal scores one of each rewrite kind before a second."""
    ranked = sorted(judged, key=lambda candidate: (candidate.score, len(candidate.chain())))
    chosen, kinds = [], set()
    for candidate in ranked:
        kind = (candidate.score, candidate.label.split('@')[0])
        if kind not in kinds:
            chosen.append(candidate)
            kinds.add(kind)
        if len(chosen) >= width:
            return chosen
    for candidate in ranked:
        if candidate not in chosen:
            chosen.append(candidate)
        if len(chosen) >= width:
            break
    return chosen


def findings_text(text):
    import check_source
    found = [f'{kind}: {message}' for _, kind, message in check_source.problems(text) + check_source.review(text)]
    return '\n'.join(found) if found else 'check_source: no findings'


def write_result(directory, name, candidate, address, start_score):
    """`name`.cpp (the source with a header) and `name`.diff (each step of the chain, the check_source findings)."""
    header = (f'// tsearch {address:06X}: score {candidate.score} (start {start_score})\n'
              f'// chain: {"; ".join(candidate.chain()) or "(start)"}\n')
    text = candidate.text
    if text.startswith('// SPDX'):
        first, rest = text.split('\n', 1)
        text = first + '\n' + header + rest
    else:
        text = header + text
    path = os.path.join(directory, f'{name}.cpp')
    with open(path, 'w', encoding='utf-8') as handle:
        handle.write(text)
    with open(os.path.join(directory, f'{name}.diff'), 'w', encoding='utf-8') as handle:
        handle.write(f'# {address:06X}: score {candidate.score} from {start_score}\n# {findings_text(candidate.text)}\n')
        for number, (label, step) in enumerate(candidate.steps(), 1):
            handle.write(f'\n# step {number}: {label}\n{step}')
    return path


def log_run(address, score, path, lang):
    """The run in work/matching/runs.log, as try.py writes it (arm `tsearch`)."""
    try:
        try_module = importlib.import_module('try')
        try_module.log_run('tsearch', address, score, path, lang, quiet=False)
    except Exception as error:  # the search result stands without the log line
        print(f'runs.log not written: {error}', file=sys.stderr)


def save_state(directory, state, beam):
    beam_files = []
    for number, candidate in enumerate(beam):
        name = f'beam_{number:02d}.src'
        with open(os.path.join(directory, name), 'w', encoding='utf-8') as handle:
            handle.write(candidate.text)
        beam_files.append({'file': name, 'score': candidate.score, 'steps': candidate.steps()})
    state['beam'] = beam_files
    with open(os.path.join(directory, 'state.json'), 'w', encoding='utf-8') as handle:
        json.dump(state, handle)


def load_state(directory):
    path = os.path.join(directory, 'state.json')
    if not os.path.exists(path):
        return None, []
    with open(path, encoding='utf-8') as handle:
        state = json.load(handle)
    beam = []
    for entry in state.get('beam', []):
        with open(os.path.join(directory, entry['file']), encoding='utf-8') as handle:
            beam.append(Candidate(handle.read(), score=entry['score'], stored_steps=[tuple(step) for step in entry['steps']],
                                  label=entry['steps'][-1][0] if entry['steps'] else None))
    return state, beam


def neighborhood_rewrites(text):
    """[(label, text)] of the rewrites of mutate.py and rules.py (neighborhood.py's single edits), for --with-neighborhood."""
    import neighborhood
    import rules
    found = []
    for changed, (name, line) in list(neighborhood.single_edits(text, 2).items()) + list(rules.edits(text).items()):
        found.append((f'neighborhood:{name}@{line + 1}', changed))
    return found


def search(address, text, lang='c++', beam=6, depth=4, budget=300, minutes=20.0, jobs=8, only=None, with_neighborhood=False, resume=False, log=print):
    """(best score, start score, compiles judged, compiles that missed the cache, the best Candidate)."""
    directory = os.path.join(OUTPUT, f'{address:06X}')
    os.makedirs(directory, exist_ok=True)
    deadline = time.time() + minutes * 60
    start_digest = digest(text)
    state, beam_set = load_state(directory) if resume else (None, [])
    if state and state.get('start') != start_digest:
        log(f'{address:06X}: the saved state is for another start source, starting again')
        state, beam_set = None, []
    start = Candidate(text)
    start.score = scorer.judge(address, text, lang)
    if start.score is None:
        log(f'{address:06X}: the start source does not compile')
        return None, None, 1, 0, start
    if state is None:
        state = {'start': start_digest, 'fingerprint': scorer.fingerprint(), 'depth': 0, 'seen': [start_digest], 'best': start.score, 'improvements': 0}
        beam_set = [start]
        with open(os.path.join(directory, 'start' + ('.c' if lang == 'c' else '.cpp')), 'w', encoding='utf-8') as handle:
            handle.write(text)
    seen = set(state['seen'])
    best = min(beam_set + [start], key=lambda candidate: candidate.score)
    best_score = min(state['best'], best.score)
    used = 0
    missed = 0
    log_file = open(os.path.join(directory, 'log.tsv'), 'a', encoding='utf-8')
    if os.path.getsize(os.path.join(directory, 'log.tsv')) == 0:
        log_file.write('depth\tscore\tcompiled\tchain\n')
    log(f'{address:06X}: start score {start.score}')
    if start.score == 0:
        log_file.close()
        return 0, 0, 1, 0, start
    with concurrent.futures.ThreadPoolExecutor(jobs) as pool:
        for level in range(state['depth'] + 1, state['depth'] + depth + 1):
            candidates = []
            for parent in beam_set:
                found = meaning_rewrites.rewrites(parent.text, only)
                if with_neighborhood:
                    found += neighborhood_rewrites(parent.text)
                for label, new in found:
                    key = digest(new)
                    if key in seen:
                        continue
                    seen.add(key)
                    if search_guard.new_findings(text, new):
                        continue
                    candidates.append(Candidate(new, label, parent))
            candidates = interleaved(candidates)[:max(0, budget - used)]
            log(f'  depth {level}: {len(candidates)} candidates from {len(beam_set)} in the beam')
            if not candidates:
                log('  nothing new to judge: the rewrites are exhausted from this beam' if used < budget else '  compile budget spent')
                break

            def judge(candidate):
                cached = scorer.cache_key(candidate.text, lang, address) in scorer.cache_for(address)
                return scorer.judge(address, candidate.text, lang), not cached

            judged = []
            for candidate, (score, compiled) in zip(candidates, pool.map(judge, candidates)):
                used += 1
                missed += compiled
                candidate.score = score
                log_file.write(f'{level}\t{"error" if score is None else score}\t{int(compiled)}\t{"; ".join(candidate.chain())}\n')
                if score is None:
                    continue
                judged.append(candidate)
                if score < best_score:
                    best_score, best = score, candidate
                    state['improvements'] += 1
                    path = write_result(directory, f'best_{state["improvements"]:02d}', candidate, address, start.score)
                    log(f'  better: {score}  {"; ".join(candidate.chain())}')
                    log_run(address, score, path, lang)
                if score == 0:
                    write_result(directory, 'zero', candidate, address, start.score)
                    log(f'  score 0: {"; ".join(candidate.chain())}')
                    break
                if time.time() > deadline:
                    break
            log_file.flush()
            state['depth'] = level
            if best_score == 0 or used >= budget or time.time() > deadline or not judged:
                beam_set = next_beam(judged, beam) or beam_set
                break
            beam_set = next_beam(judged, beam)
    log_file.close()
    state['best'] = best_score
    state['seen'] = sorted(seen)
    state['used_total'] = state.get('used_total', 0) + used
    save_state(directory, state, beam_set)
    log(f'{address:06X}: best {best_score} (start {start.score}) after {used} judged, {missed} compiled; chain: {"; ".join(best.chain()) or "(start)"}')
    return best_score, start.score, used, missed, best


def pool_of(arguments):
    """[(score, address, path)] of the near misses to search: the addresses of --addresses, else the manifest's scores in the range."""
    pool = []
    if arguments.addresses:
        with open(arguments.addresses, encoding='utf-8') as handle:
            addresses = [int(line.split()[0], 16) for line in handle if line.strip() and not line.startswith('#')]
    else:
        with open(MANIFEST, encoding='utf-8') as handle:
            addresses = [int(row['address'], 16) for row in csv.DictReader(handle, delimiter='\t')
                         if row['score'].isdigit() and arguments.min_score <= int(row['score']) <= arguments.max_score]
    for address in addresses:
        reason = search_guard.skipped(address)
        if reason:
            print(f'{address:06X}: skipped ({reason})', file=sys.stderr)
            continue
        path = source_path(address)
        if path:
            pool.append((address, path))
    return pool


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('address', nargs='?')
    parser.add_argument('source', nargs='?')
    parser.add_argument('--batch', action='store_true')
    parser.add_argument('--addresses', help='a file of addresses (first column), for --batch')
    parser.add_argument('--min-score', type=int, default=5)
    parser.add_argument('--max-score', type=int, default=16)
    parser.add_argument('--beam', type=int, default=6)
    parser.add_argument('--depth', type=int, default=4)
    parser.add_argument('--budget', type=int, default=300, help='candidates judged per function (a cache hit counts too)')
    parser.add_argument('--minutes', type=float, default=20.0, help='per function')
    parser.add_argument('--jobs', type=int, default=8)
    parser.add_argument('--only', help='comma-separated rewrite names (meaning_rewrites.py --list)')
    parser.add_argument('--with-neighborhood', action='store_true', help="also neighborhood.py's rewrites (mutate.py, rules.py), which do not all keep meaning")
    parser.add_argument('--resume', action='store_true', help='continue from state.json')
    arguments = parser.parse_args()
    if not scorer.compare:
        sys.exit('needs rabbitizer and pyelftools: run with .venv/bin/python')
    only = set(arguments.only.split(',')) if arguments.only else None
    options = dict(beam=arguments.beam, depth=arguments.depth, budget=arguments.budget, minutes=arguments.minutes, jobs=arguments.jobs, only=only,
                   with_neighborhood=arguments.with_neighborhood, resume=arguments.resume)
    scorer.registry()
    if arguments.batch:
        pool = pool_of(arguments)
        print(f'{len(pool)} functions, budget {arguments.budget}, beam {arguments.beam}, depth {arguments.depth}')
        progress = Progress(len(pool), 'tsearch')
        improved = reached = 0
        for index, (address, path) in enumerate(pool, 1):
            progress.begin(f'{address:06X}')
            with open(path, encoding='utf-8') as handle:
                text = handle.read()
            best, start, used, missed, _ = search(address, text, language_of(path), log=lambda message: None, **options)
            progress.tick(f'{address:06X}: {start} -> {best}', f'{address:06X}')
            print(f'[{index}/{len(pool)}] {address:#X}: {start} -> {best} ({used} judged, {missed} compiled){progress.suffix()}', flush=True)
            if best is not None and start is not None and best < start:
                improved += 1
                reached += best == 0
        print(f'{len(pool)} functions: {improved} improved, {reached} reach 0 (work/matching/tsearch/)')
        return 0
    if not arguments.address:
        parser.error('an address or --batch')
    address = int(arguments.address, 16)
    reason = search_guard.skipped(address)
    if reason:
        print(f'{address:06X}: skipped ({reason})')
        return 0
    path = arguments.source or source_path(address)
    if not path:
        sys.exit(f'no source for {address:06X}')
    with open(path, encoding='utf-8') as handle:
        text = handle.read()
    search(address, text, language_of(path), **options)
    return 0


if __name__ == '__main__':
    sys.exit(main())
