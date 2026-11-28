#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""sitesearch.py - candidate statements written in at one site of a near miss, every candidate keeping the function's meaning.

  .venv/bin/python scripts/matching/sitesearch.py 0x1C7C30 [SOURCE] [--generator NAME,...] [--line N] [--budget 300] [--jobs 8] [--list]
  .venv/bin/python scripts/matching/sitesearch.py --generators

tsearch.py rewrites the statements a source has; a near miss sometimes needs a statement it does not have: the same store written in both
arms, a field read once into a local, a clamp in another of its four forms, a flag computed as a value, a counted loop counting down, a copy
of a variable after a join, an empty `case` the jump table shows. Each generator below knows where such a statement can stand (its sites)
and what it may be there (its forms), and yields every candidate; a candidate is the whole source with the statement written in. The forms
are the ones measured on our near misses and in sly1-decomp's toolchain notes (docs/IDEAS.md sections 4 and 5, docs/contributing/matching.md
"Levers"); sly1-decomp's tools/sitesearch.py (AGPL-3.0, read for the idea only; it has one generator for one function) is not used.

Unlike sly1-decomp's, no generator here writes a statement that is not the original's in meaning: each one is checked like tsearch.py's
rewrites (no side effect duplicated or moved across one that could see it) and must add no finding (search_guard.py, check_source.py).

Everything goes to work/matching/sitesearch/<ADDRESS>/: log.tsv (start source, generator, line, label, score; a rerun skips the labels it
holds for the same start source, so a long run can be stopped and resumed), better_NN.cpp/.diff for each improvement and zero.cpp/.diff for
a score of 0 (a lead until `make land` passes). Improvements and zeros are also logged in work/matching/runs.log (arm `sitesearch`)."""
import argparse
import concurrent.futures
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import meaning_rewrites  # noqa: E402
from meaning_rewrites import (arm_statements, assignment_of, declaration, ends_in_exit, expression_type, fresh_name, has_labels, is_pure,  # noqa: E402
                              is_simple_lvalue, is_written_place, line_of, line_text, literal_value, negation, plain_scalar_type, reads_target,
                              reindent, single, statement_nodes, statements_text, switch_groups, unit_indent, BOOLEAN_OPERATORS)
from source_tree import ParseError, Source, apply_edits, normalized, strip_parentheses  # noqa: E402

LAB = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
OUTPUT = os.path.join(LAB, 'work', 'matching', 'sitesearch')


def store_in_both_arms(source):
    """`x = v; if (c) A else B` as `if (c) { x = v; A } else { x = v; B }` (an if without else gains `else { x = v; }`), and with the store
    at the end of each arm where neither arm reads x or changes what v reads. c and v have no side effects and c does not read x.
    docs/IDEAS.md 4 ("Store and test written in each arm"), lessons.md."""
    if has_labels(source):
        return []
    found = []
    parents = source.parent_map()
    step = unit_indent(source)
    for statement in source.body.walk():
        if statement.kind != 'if':
            continue
        parent = parents.get(id(statement))
        if not parent or parent[0].kind != 'block' or parent[1] == 0:
            continue
        before = parent[0].parts['statements'][parent[1] - 1]
        assignment = assignment_of(before)
        lines = line_text(source, before)
        condition = statement.parts['condition']
        if not assignment or not lines or not is_simple_lvalue(source, assignment[0]) or not is_pure(source, assignment[1]) or not is_pure(source, condition) \
                or reads_target(source, condition, assignment[0]):
            continue
        store = source.source_of(before)
        indent = source.indent_of(statement)
        then, otherwise = statement.parts['then'], statement.parts['otherwise']
        if otherwise is not None and otherwise.kind == 'if':
            continue
        store_effects = source.effects(before)
        for placement in ('start', 'end'):
            arms = [then] + ([otherwise] if otherwise is not None else [])
            if placement == 'end' and any(store_effects.conflicts(source.effects(arm)) or ends_in_exit(arm) for arm in arms):
                continue
            texts = []
            for arm in arms:
                inner = statements_text(source, arm_statements(arm), indent + step)
                body = [indent + step + store, inner] if placement == 'start' else [inner, indent + step + store]
                texts.append('{\n' + '\n'.join(part for part in body if part) + '\n' + indent + '}')
            if otherwise is None:
                texts.append('{\n' + indent + step + store + '\n' + indent + '}')
            text = f'if ({source.source_of(condition)}) {texts[0]} else {texts[1]}'
            found.append((line_of(source, statement), f'store_in_both_arms@{line_of(source, statement)} {placement}',
                          [(lines[0], lines[1], ''), (*source.span(statement), text)]))
    return found


def read_once_local(source):
    """A member or element read of a statement (no call in it) named by a local of its type declared just before: `T f = p->f;
    use(f)`. docs/contributing/matching.md ("Read a member into a local", wave S14), docs/IDEAS.md 1."""
    found = []
    parents = source.parent_map()
    for statement in source.body.walk():
        if statement.kind not in ('expression', 'return'):
            continue
        parent = parents.get(id(statement))
        lines = line_text(source, statement)
        if not parent or parent[0].kind != 'block' or not lines:
            continue
        effects = source.effects(statement)
        if effects.call:
            continue
        root = statement.parts.get('expression') if statement.kind == 'expression' else statement.parts.get('value')
        if root is None:
            continue
        assignment = assignment_of(statement)
        value = assignment[1] if assignment else root
        if assignment is None and statement.kind == 'expression':
            continue
        if not is_pure(source, value):
            continue
        indent = source.indent_of(statement)
        seen = set()
        for node in value.walk():
            if node.kind not in ('member', 'index') or is_written_place(source, node) or source.tokens[node.first - 1].text == '&':
                continue
            key = normalized(source.source_of(node))
            type_text = expression_type(source, node)
            if key in seen or not type_text or not plain_scalar_type(type_text):
                continue
            seen.add(key)
            base_name = source.tokens[node.last].text if node.kind == 'member' else 'element'
            name = fresh_name(source, base_name)
            edits = [(lines[0], lines[0], f'{indent}{declaration(type_text, name, source.source_of(node))}\n')]
            edits += [(*source.span(other), name) for other in value.walk() if other.kind == node.kind and normalized(source.source_of(other)) == key]
            if len({edit[0] for edit in edits[1:]}) != len(edits) - 1:
                continue
            found.append((line_of(source, statement), f'read_once_local@{line_of(source, statement)} {key}', edits))
    return found


def substitute_name(source, node, name, replacement):
    """The text of `node` with every plain use of the local `name` written as `(replacement)`."""
    text = source.source_of(node)
    offset = source.tokens[node.first].start
    plain = re.fullmatch(r'[\w.]+', replacement) is not None
    edits = [(source.tokens[index].start - offset, source.tokens[index].end - offset, replacement if plain else f'({replacement})')
             for index in source.uses(name, node.first, node.last)]
    return apply_edits(text, edits)


def clamp_forms(source):
    """A conditional store in the forms the compiler tells apart: `v = X; if (c) v = Y;`, `v = Y; if (!c) v = X;`, `if (c) v = Y; else
    v = X;` and `v = c ? Y : X;` (X, Y and c without side effects, X and Y not reading v; a c that reads v after `v = X` has X written in
    its place). The negated comparison is exact on the PS2 (no NaN). docs/IDEAS.md 5 ("jump.c clamp form"), docs/contributing/matching.md
    wave Y19 (`if` forms for clamps)."""
    if has_labels(source):
        return []
    found = []
    parents = source.parent_map()
    step = unit_indent(source)
    for statement in source.body.walk():
        if statement.kind != 'if':
            continue
        parent = parents.get(id(statement))
        if not parent or parent[0].kind != 'block':
            continue
        then, otherwise = statement.parts['then'], statement.parts['otherwise']
        conditional = assignment_of(single(then)) if single(then) else None
        if conditional is None or not is_simple_lvalue(source, conditional[0]):
            continue
        target = strip_parentheses(conditional[0])
        target_text = source.source_of(conditional[0])
        condition = statement.parts['condition']
        if otherwise is None and parent[1] > 0:
            before = parent[0].parts['statements'][parent[1] - 1]
            initial = assignment_of(before)
            if not initial or normalized(source.source_of(initial[0])) != normalized(target_text):
                continue
            span = (source.span(before)[0], source.span(statement)[1])
            low, high = initial[1], conditional[1]
            if target.kind == 'name' and source.tracked(target.operator):
                test = substitute_name(source, condition, target.operator, source.source_of(low))
            elif reads_target(source, condition, conditional[0]):
                continue
            else:
                test = source.source_of(condition)
            forms = ['negated', 'if/else', 'ternary']
        elif otherwise is not None and single(otherwise) and assignment_of(single(otherwise)) \
                and normalized(source.source_of(assignment_of(single(otherwise))[0])) == normalized(target_text) and not reads_target(source, condition, conditional[0]):
            span = source.span(statement)
            low, high = assignment_of(single(otherwise))[1], conditional[1]
            test = source.source_of(condition)
            forms = ['store first', 'negated', 'ternary']
        else:
            continue
        if not (is_pure(source, low) and is_pure(source, high) and is_pure(source, condition)) or reads_target(source, low, conditional[0]) or reads_target(source, high, conditional[0]):
            continue
        indent = source.indent_of(statement)
        test_source = Source(f'void probe() {{ if ({test}) ; }}')
        negated = negation(test_source, test_source.body.parts['statements'][0].parts['condition'])
        low_text, high_text = source.source_of(low), source.source_of(high)
        texts = {'store first': f'{target_text} = {low_text};\n{indent}if ({test})\n{indent}{step}{target_text} = {high_text};',
                 'negated': f'{target_text} = {high_text};\n{indent}if ({negated})\n{indent}{step}{target_text} = {low_text};',
                 'if/else': f'if ({test})\n{indent}{step}{target_text} = {high_text};\n{indent}else\n{indent}{step}{target_text} = {low_text};',
                 'ternary': f'{target_text} = ({test}) ? {high_text} : {low_text};'}
        for form in forms:
            found.append((line_of(source, statement), f'clamp_forms@{line_of(source, statement)} {form}', [(*span, texts[form])]))
    return found


def is_boolean(node):
    node = strip_parentheses(node)
    return (node.kind == 'binary' and node.operator in BOOLEAN_OPERATORS) or (node.kind == 'unary' and node.operator == '!')


def flag_as_value(source):
    """`flag = 0; if (cond) flag = 1;` (or `T flag = 0;` then the if) as `flag = cond;` (`cond != 0` when cond is not itself a test), and the
    reverse; cond does not read flag. docs/IDEAS.md 5 ("Flag as a value"), rules.py result_local for the return form."""
    if has_labels(source):
        return []
    found = []
    parents = source.parent_map()
    step = unit_indent(source)
    for statement in source.body.walk():
        parent = parents.get(id(statement))
        if not parent or parent[0].kind != 'block':
            continue
        indent = source.indent_of(statement)
        if statement.kind == 'if' and statement.parts['otherwise'] is None and parent[1] > 0:
            conditional = assignment_of(single(statement.parts['then'])) if single(statement.parts['then']) else None
            before = parent[0].parts['statements'][parent[1] - 1]
            if conditional is None or literal_value(conditional[1]) != 1 or strip_parentheses(conditional[0]).kind != 'name':
                continue
            name = strip_parentheses(conditional[0]).operator
            condition = statement.parts['condition']
            if not source.tracked(name) or name in source.node_effects(condition).reads:
                continue
            value = source.source_of(strip_parentheses(condition)) if is_boolean(condition) else f'{source.source_of(condition)} != 0'
            initial = assignment_of(before)
            if initial and strip_parentheses(initial[0]).kind == 'name' and strip_parentheses(initial[0]).operator == name and literal_value(initial[1]) == 0:
                found.append((line_of(source, statement), f'flag_as_value@{line_of(source, statement)} {name} as a value',
                              [(source.span(before)[0], source.span(statement)[1], f'{name} = {value};')]))
            elif before.kind == 'declaration' and len(before.parts['declarators']) == 1 and before.parts['declarators'][0].name == name \
                    and before.parts['declarators'][0].initializer is not None and literal_value(before.parts['declarators'][0].initializer) == 0:
                found.append((line_of(source, statement), f'flag_as_value@{line_of(source, statement)} {name} declared as a value',
                              [(source.span(before)[0], source.span(statement)[1], declaration(source.type_of_local(name), name, value))]))
        assignment = assignment_of(statement)
        if assignment and strip_parentheses(assignment[0]).kind == 'name' and is_boolean(assignment[1]):
            name = strip_parentheses(assignment[0]).operator
            if source.tracked(name) and name not in source.node_effects(assignment[1]).reads:
                text = f'{name} = 0;\n{indent}if ({source.source_of(strip_parentheses(assignment[1]))})\n{indent}{step}{name} = 1;'
                found.append((line_of(source, statement), f'flag_as_value@{line_of(source, statement)} {name} as a conditional store', [(*source.span(statement), text)]))
    return found


def countdown_loops(source):
    """`for (i = 0; i < n; i++)` whose counter is read nowhere else (not in the body, not after the loop) counting down instead:
    `for (i = n; i > 0; i--)`, `for (i = n; --i >= 0;)` (signed counters), `for (i = n; i-- > 0;)`, and `!= 0` and `while (i--)` forms where
    n is a literal that is not negative. n has no side effects and the body does not change it. docs/IDEAS.md 4 ("for (i = n; --i >= 0;)
    and count-down forms"), the fmodf loop of section 0."""
    if has_labels(source):
        return []
    found = []
    for statement in source.body.walk():
        if statement.kind != 'for':
            continue
        init, condition, step, body = (statement.parts[key] for key in ('init', 'condition', 'step', 'body'))
        if init is None or condition is None or step is None:
            continue
        if init.kind == 'declaration' and len(init.parts['declarators']) == 1 and init.parts['declarators'][0].initializer is not None:
            counter, start, declared = init.parts['declarators'][0].name, init.parts['declarators'][0].initializer, source.type_of_local(init.parts['declarators'][0].name)
        elif init.kind == 'expression' and assignment_of(init) and strip_parentheses(assignment_of(init)[0]).kind == 'name':
            counter, start, declared = strip_parentheses(assignment_of(init)[0]).operator, assignment_of(init)[1], None
        else:
            continue
        test, step_node = strip_parentheses(condition), strip_parentheses(step)
        if literal_value(start) != 0 or test.kind != 'binary' or test.operator != '<' or strip_parentheses(test.children[0]).kind != 'name' \
                or strip_parentheses(test.children[0]).operator != counter:
            continue
        if not (step_node.kind in ('postfix', 'unary') and step_node.operator == '++' and strip_parentheses(step_node.children[0]).operator == counter):
            continue
        if not source.tracked(counter) or source.uses(counter, body.first, body.last):
            continue
        outside = [index for index in source.uses(counter) if not (statement.first <= index <= statement.last)]
        if counter in source.declarations and source.declarations[counter][0] is not init:
            outside = [index for index in outside if index != source.declarations[counter][1].name_token]
        if outside:
            continue
        bound = test.children[1]
        bound_effects, body_effects = source.node_effects(bound), source.effects(body)
        if not is_pure(source, bound) or bound_effects.reads & body_effects.writes or (bound_effects.memory_read and (body_effects.memory_write or body_effects.call)):
            continue
        type_text = declared or source.type_of_local(counter) or 'int'
        unsigned = 'unsigned' in type_text or re.match(r'\s*u\d', type_text) is not None
        prefix = f'{type_text} ' if init.kind == 'declaration' else ''
        bound_text = source.source_of(bound)
        closer = source.matching(statement.first + 1)
        headers = [f'for ({prefix}{counter} = {bound_text}; {counter} > 0; {counter}--)', f'for ({prefix}{counter} = {bound_text}; {counter}-- > 0;)']
        if not unsigned:
            headers.append(f'for ({prefix}{counter} = {bound_text}; --{counter} >= 0;)')
        if literal_value(bound) is not None and literal_value(bound) >= 0:
            headers.append(f'for ({prefix}{counter} = {bound_text}; {counter} != 0; {counter}--)')
            headers.append(f'for ({prefix}{counter} = {bound_text}; {counter}--;)')
        for header in headers:
            found.append((line_of(source, statement), f'countdown_loops@{line_of(source, statement)} {header}', [(source.tokens[statement.first].start, source.tokens[closer].end, header)]))
    return found


def copy_after_join(source):
    """After an if, a loop or a switch that writes a local, the local copied (`T last = c;`) and the reads that follow in its block, up to
    the next write of it, made through the copy. docs/IDEAS.md 4 ("Single `last = c;` after a join")."""
    if has_labels(source):
        return []
    found = []
    for block in source.blocks():
        items = block.parts['statements']
        for position, statement in enumerate(items[:-1]):
            if statement.kind not in ('if', 'while', 'do', 'for', 'switch'):
                continue
            lines = line_text(source, statement)
            if not lines:
                continue
            for name in sorted(source.effects(statement).writes):
                type_text = source.type_of_local(name)
                if not plain_scalar_type(type_text) or not source.tracked(name):
                    continue
                uses = []
                for item in items[position + 1:]:
                    if item.kind in ('case', 'label') or name in source.effects(item).writes:
                        break
                    uses.extend(source.uses(name, item.first, item.last))
                if not uses:
                    continue
                copy = fresh_name(source, 'last')
                indent = source.indent_of(statement)
                edits = [(lines[1], lines[1], f'{indent}{declaration(type_text, copy, name)}\n')]
                edits += [(source.tokens[index].start, source.tokens[index].end, copy) for index in uses]
                found.append((line_of(source, statement), f'copy_after_join@{line_of(source, statement)} {name} copied after the join', edits))
    return found


def empty_case(source):
    """An empty `case K: break;` added to a switch with no default (or a default that only breaks), for the values next to and between its
    labels, at its start and at its end: the case tree and jump table follow the labels. docs/IDEAS.md 4 ("Empty second `case`"),
    docs/contributing/matching.md waves S14 and Z30 (`case 0: break;` in a final switch)."""
    found = []
    for statement in source.body.walk():
        if statement.kind != 'switch':
            continue
        groups = switch_groups(source, statement)
        if not groups:
            continue
        values, plain = [], True
        for labels, statements in groups:
            for label in labels:
                if label.parts['value'] is None:
                    plain = plain and len(statements) == 1 and statements[0].kind == 'break'
                else:
                    value = literal_value(label.parts['value'])
                    if value is None:
                        plain = False
                    else:
                        values.append(value)
        if not plain or not values:
            continue
        candidates = [min(values) - 1, max(values) + 1] + [value for value in range(min(values), max(values)) if value not in values][:3]
        candidates = [value for value in dict.fromkeys(candidates) if value >= 0 or min(values) < 0]
        first_label = groups[0][0][0]
        start = line_text(source, first_label)
        body = statement.parts['body']
        closing_line = source.text.rfind('\n', 0, source.tokens[body.last].start) + 1
        if not start or source.text[closing_line:source.tokens[body.last].start].strip():
            continue
        label_indent = source.indent_of(first_label)
        inner_indent = label_indent + unit_indent(source)
        for value in candidates:
            text = f'{label_indent}case {value}:\n{inner_indent}break;\n'
            found.append((line_of(source, statement), f'empty_case@{line_of(source, statement)} case {value} first', [(start[0], start[0], text)]))
            found.append((line_of(source, statement), f'empty_case@{line_of(source, statement)} case {value} last', [(closing_line, closing_line, text)]))
    return found


GENERATORS = [store_in_both_arms, read_once_local, clamp_forms, flag_as_value, countdown_loops, copy_after_join, empty_case]
BY_NAME = {generator.__name__: generator for generator in GENERATORS}


def candidates(text, generators=None, line=None, function=None):
    """[(generator, line, label, new text)] of every generator's candidates that apply, parse again and add no forbidden construct."""
    import search_guard
    try:
        source = Source(text, function)
    except (ParseError, RecursionError, IndexError):
        return []
    found, seen = [], {normalized(text)}
    for generator in GENERATORS:
        if generators and generator.__name__ not in generators:
            continue
        try:
            produced = generator(source)
        except (ParseError, IndexError, KeyError, ValueError, RecursionError, StopIteration, AttributeError, TypeError):
            continue
        for site, label, edits in produced:
            if line is not None and site != line:
                continue
            if meaning_rewrites.overlapping(edits):
                continue
            new = apply_edits(text, edits)
            key = normalized(new)
            if key in seen or meaning_rewrites.forbidden(text, new) or search_guard.new_findings(text, new):
                continue
            try:
                Source(new, function)
            except (ParseError, RecursionError, IndexError):
                continue
            seen.add(key)
            found.append((generator.__name__, site, label, new))
    return found


def read_log(path):
    """{(start digest, label): score} of a log.tsv."""
    done = {}
    if os.path.exists(path):
        with open(path, encoding='utf-8') as handle:
            for line in handle.read().splitlines()[1:]:
                fields = line.split('\t')
                if len(fields) >= 5:
                    done[(fields[0], fields[3])] = fields[4]
    return done


def run(address, text, lang='c++', generators=None, line=None, budget=300, jobs=8, log=print):
    """(best score, start score, candidates judged, compiles that missed the cache)."""
    import scorer
    import tsearch
    directory = os.path.join(OUTPUT, f'{address:06X}')
    os.makedirs(directory, exist_ok=True)
    log_path = os.path.join(directory, 'log.tsv')
    done = read_log(log_path)
    start_digest = tsearch.digest(text)
    start = tsearch.Candidate(text)
    start.score = scorer.judge(address, text, lang)
    if start.score is None:
        log(f'{address:06X}: the start source does not compile')
        return None, None, 1, 0
    pending = [item for item in candidates(text, generators, line) if (start_digest, item[2]) not in done][:budget]
    log(f'{address:06X}: start score {start.score}, {len(pending)} candidates to judge ({sum(1 for key in done if key[0] == start_digest)} already in the log)')
    best_score, improvements, missed = start.score, len([name for name in os.listdir(directory) if name.startswith('better_') and name.endswith('.cpp')]), 0

    def judge(item):
        cached = scorer.cache_key(item[3], lang, address) in scorer.cache_for(address)
        return scorer.judge(address, item[3], lang), not cached

    new_log = not os.path.exists(log_path)
    with open(log_path, 'a', encoding='utf-8') as handle, concurrent.futures.ThreadPoolExecutor(jobs) as pool:
        if new_log:
            handle.write('start\tgenerator\tline\tlabel\tscore\n')
        for item, (score, compiled) in zip(pending, pool.map(judge, pending)):
            missed += compiled
            handle.write(f'{start_digest}\t{item[0]}\t{item[1]}\t{item[2]}\t{"error" if score is None else score}\n')
            if score is not None and score < best_score:
                best_score = score
                improvements += 1
                candidate = tsearch.Candidate(item[3], item[2], start, score)
                path = tsearch.write_result(directory, 'zero' if score == 0 else f'better_{improvements:02d}', candidate, address, start.score)
                log(f'  better: {score}  {item[2]}')
                log_run(address, score, path, lang)
    log(f'{address:06X}: best {best_score} (start {start.score}) after {len(pending)} judged, {missed} compiled')
    return best_score, start.score, len(pending), missed


def log_run(address, score, path, lang):
    import importlib
    try:
        importlib.import_module('try').log_run('sitesearch', address, score, path, lang, quiet=False)
    except Exception as error:
        print(f'runs.log not written: {error}', file=sys.stderr)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('address', nargs='?')
    parser.add_argument('source', nargs='?')
    parser.add_argument('--generator', help='comma-separated generator names (--generators lists them)')
    parser.add_argument('--line', type=int, help='only the site at this line of the source')
    parser.add_argument('--budget', type=int, default=300, help='candidates judged in this run (a cache hit counts too)')
    parser.add_argument('--jobs', type=int, default=8)
    parser.add_argument('--list', action='store_true', help='print the candidates as diffs, compile nothing')
    parser.add_argument('--generators', action='store_true', help='the generators and what each writes')
    arguments = parser.parse_args()
    if arguments.generators or not arguments.address:
        for generator in GENERATORS:
            print(f'{generator.__name__:20} {" ".join(generator.__doc__.split())}')
        return 0
    import search_guard
    import tsearch
    address = int(arguments.address, 16)
    path = arguments.source or tsearch.source_path(address)
    if not path:
        sys.exit(f'no source for {address:06X}')
    with open(path, encoding='utf-8') as handle:
        text = handle.read()
    generators = set(arguments.generator.split(',')) if arguments.generator else None
    if arguments.list:
        for generator, site, label, new in candidates(text, generators, arguments.line):
            print(f'== {label}')
            print(meaning_rewrites.diff(text, new))
        return 0
    reason = search_guard.skipped(address)
    if reason:
        print(f'{address:06X}: skipped ({reason})')
        return 0
    import scorer
    if not scorer.compare:
        sys.exit('needs rabbitizer and pyelftools: run with .venv/bin/python')
    run(address, text, tsearch.language_of(path), generators, arguments.line, arguments.budget, arguments.jobs)
    return 0


if __name__ == '__main__':
    sys.exit(main())
