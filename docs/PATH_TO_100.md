# Path to 100%

Drafted 2026-11-15 from `progress/us/report.json` and `scripts/list_functions.py`. Numbers move; re-measure before each stage.
Order and policy follow [AGENT_WORKFLOW.md](AGENT_WORKFLOW.md) and [ROADMAP.md](ROADMAP.md); the rules are in AGENTS.md.

## Where we are (2026-11-15)

- Code matched: 70.26% (5,533 of 6,061 functions; the 809 permanent blockers are left out of the totals).
- Work queue: 477 unmatched functions: 428 with a draft in `nonmatching/`, 49 without one (SDK range, asm only).
- Data: 33.95% (ceiling about 49%).
- PAL: 99 functions do not reproduce from the same C.

## What "100%" means

Three separate targets. Only the first is a matching goal.

| Target | Meaning | State |
| :--- | :--- | :--- |
| A. C-expressible code | every function outside the blockers scores 0 and `make elf` passes | 70.26% |
| B. Whole image | `make elf` reproduces retail byte for byte | holds today (blockers stay original assembly) |
| C. Data | data defined from C where a reader shows its type | 33.95%, ceiling about 49% |

The 809 blockers (VU0, MMI, COP0, hand-written, remnants) stay original assembly by rule, so exact C tops out near 83% of
all code. Track B is a gate, not work.

## Track A: C-expressible code

Stages run in order. Status: Not Started | In Progress | Complete.

### Stage 1: the 49 functions with no draft (In Progress)

Why first: no draft means nothing to improve, so each is either a quick win or a measured wall, and the answer feeds every later stage.

- List: `python3 scripts/list_functions.py --status asm --sort size`.
- By size: Haiku up to 400 bytes, Sonnet 401 to 1,000, Opus above. Contiguous functions go to one worker. About ten compiles per function, then hand the best attempt up a tier.
- Most are SDK range (`config/us/sony_gcc29.txt`, Sony gcc 2.9). Use `compile_unit.py` with the sony29 runner; libm needs 991111-01.
- Output per function: a match, or a draft in `nonmatching/` with `MANIFEST.tsv` score, or `SKIP wall <semantics>`.
- Status 2026-11-15: since the list was drawn, these are matched or published (matched: `func_0023E618`,
  `__eh_rtime_match`, `func_002405F0`, `func_0023AA98`, `func_0023AAB8`; drafts: `GetXfDofValue`, `InsertTargetCandidate`,
  `EvaluateAcsb`, `DtSolveJumpLaunch`, `GetJoyXYDeflection`); six more have a blocker note (`0x100000`, `exit_thunk`,
  `0x119BC0`, `0x14C1E0`, `0x243ED8`, `0x241970`). Left: the VU0 and asm-draft group, `__throw`, and the four large ones.
- Exit: every one of the 49 has a match or a draft. Re-run `classify_diffs.py` on the new drafts and record the wall classes.

### Stage 2: near misses (Not Started)

- 102 drafts within 16 words of retail go to Opus, one function per worker, with the earlier attempt and its diff.
- Six integer near misses have no known lever: 0x1733C8, 0x120548, 0x218748, 0x1A5D98, 0x13FAD0 (0x1C9058 now has a flag row). Check the RTL dump first.
- SDK near misses: `powf` and the 5 libm drafts.

### Stage 3: levers before waves (Not Started)

Waves yield about 20 bytes per claimed function. What moved the number: loop5, `-fmove-all-movables`, `function_flags.tsv`, shared helpers.

- Group the drafts by wall class (`classify_diffs.py`, never an ad-hoc parser).
- One measured lever per class, against a control. Land it, then `rejudge.py` the affected drafts.
- Run a wave only on a class where a lever just landed.

### Stage 4: inline kind (Not Started)

- 133 functions, about 11% of code, compiled C that needs the shared helpers.
- A new helper goes into `include/ps2inline.h` or `include/vu0inline.h`, measured on more than one function: one instruction each, no register pins, no `"memory"` clobber.

### Stage 5: SDK range drafting (Not Started)

- Remaining libm and libc giants. Drafting work, not toolchain.

### Stage 6: tail (Not Started)

- What is left after stages 1 to 5 is a permanent wall.
- Each gets one line of semantics in `config/us/blocker_notes.tsv` (PS2 FPU behaviour where it matters).
- Report these as walls. Do not count equivalent C.

Expected ceiling: the 90s of the C-expressible code, not 100%. Stage 6 decides the number.

## Track C: data

- Typed data from C only where the initial value reproduces retail's bytes at its address; `// data-ok: typed from <reader>`.
- Needs types from readers, not matching.
- Finish the 10 whole files still not proved (`po_screen_210eb0`, `SyncVBlank_file`, `StartupJmt_file`, `PloFindSpawn_file`, `QueueSwCallback_file`, `PsoHitTestLineObjects_file`, and the four with flag lists).
- The irx and vutext regions are not game C and stay out.

## Cross-cutting

- `make pal` after each land; commit `config/eu/` and `progress/eu/report.json`. A function that no longer reproduces PAL is a finding.
- Shared types before more matches land on padded structs: `GUARD`, `JT`, the `CRef` remainder, the `aseg` segment type.
- Per stage, before committing: `make check`, `make elf`, `make objdiff`, `make readme`. Run `make` with `PROGRESS=0`.
- Costs: `python3 scripts/cost_report.py` after each large step; append a dated row to `docs/costs.md`.

## Unresolved questions

- Which "100%" is the headline: the report's matched-code %, every function with a draft scoring 0, or image bytes (already true)?
- Reservation: stages 1 and 2 are about 150 functions; stage 4 adds 133. Under the 500 cap, but check the coordination comment first.
- Is track C in scope for this path, or code only?
- Move this into ROADMAP "Next" once agreed?
