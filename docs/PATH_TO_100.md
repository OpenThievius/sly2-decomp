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

### Stage 2: near misses (In Progress)

- Status 2026-11-15: wave S2 (102 drafts scoring 1 to 16) ran with 12 Opus workers; 33 reached 0 (matched code 70.76% to 71.92%, 5548 to 5583 functions). Recurring walls: early `%hi` kept across a call (8 drafts), volatile store in a delay slot (5), pextlw reload (3), VU0 register order (4).

- 102 drafts within 16 words of retail go to Opus, one function per worker, with the earlier attempt and its diff.
- Six integer near misses had no known lever: 0x1733C8, 0x120548, 0x218748, 0x1A5D98, 0x13FAD0 and 0x1C9058; five are matched by 2026-11-16 (see stage 3), 0x1C9058 is a noted wall.
- SDK near misses: `powf` and the 5 libm drafts.

### Stage 3: levers before waves (In Progress)

- Status 2026-11-16: four more levers landed as matches (matching.md, "What usually fixes a near miss"): scaled index first in an address sum, one `switch` arm per case, `return fixed >> 32` for a truncated `long`, and a table copied from its data global. They took `AddSpawnerOffset`, `bevy_splice_bif_ref_op_eqv` and `PauseSpriteInstance` (waves S6-<addr>) to 0; `StartLoadingLogo` stays at 9 (a high-part register tie, noted). Matched code 73.46%, 5,598 of 6,063 functions. Of the six integer near misses, five are matched; `StartLoadingLogo` is the one left.
- Status 2026-11-15: `VectorFromFloats3` (one helper for the mfc1/pextlw/pcpyld block) landed, 3 matches (`SetVectorCylind`, `SetVectorSphere`, `GetXfDofValue`). Closed with no rule-clean lever: the early `%hi` across a save call (cse-and-pre.md section 4), the VU0 register order of `ScaleByReciprocalX` and `DotProduct`. Volatile store in a branch or jal delay slot (5 drafts): toolchain limit, no assembler fills it. Next: the 4-lane pextlw variant, register-allocation classes, a new wave only where a lever landed.

Waves yield about 20 bytes per claimed function. What moved the number: loop5, `-fmove-all-movables`, `function_flags.tsv`, shared helpers.

- Group the drafts by wall class (`classify_diffs.py`, never an ad-hoc parser).
- One measured lever per class, against a control. Land it, then `rejudge.py` the affected drafts.
- Run a wave only on a class where a lever just landed.

### Stage 4: inline kind (In Progress)

- Status 2026-11-15: only 12 of the 219 inline-kind functions were still in assembly (all VU0, 24,200 bytes), not 133. Waves S4 and S4a to S4h: 0 matches, 9 near misses and drafts rewritten onto shared helpers (`RefOpMult` 282 to 33, `func_001CC2E8` 105 to 4, `UpdateGuardSensor` 43 to 26 with a `-fno-strength-reduce` row, `UpdateVehicle` 531 to 43, `RenderGlobsetTree` 846 to 547). `ScaleAddTwoX` landed (two users). `RenderGlobsetTree` has a named exception for its microprogram's fixed registers (AGENTS.md, 2026-11-15). Worker lesson: `claim.py take` is arrival order, so one wave per target function.
- Status 2026-11-16 (waves S7-<addr>, one function each): `RenderGlobsetTree` 881 to 328 (the registry's 547 was an older rewrite), with the VIF/DMA stream written as inline member functions of `VIFS`, `matBone` assigned not initialised, the quad copy as four loads then four stores, and the kind adjust as a `switch`; it cannot land while its `vcallms` and `cfc2.i` statements are inline asm (`check_source.py`; the register-variable lines carry the marker). Recommendation, not a ruling: leave the asm ruling until the score is close, since 328 words are far from 0. `func_001B8D30`: the registry's 4 was a draft with its own inline asm and a pointer local; the rule-clean best is 9 (stack slots of the scale temporary, 7 words, plus a late `lwc1`). `func_001CC2E8` 4: matches only with a two-input-operand `DotProductXy` (`vmul.xy` + `vaddy.x`), two instructions and one measured user, so not added to `vu0inline.h` (noted in `blocker_notes.tsv`).
- Left: the three above, `UpdateVehicle` (43), `UpdateGuardSensor` (26), `RefOpMult` (33).
- 133 functions, about 11% of code, compiled C that needs the shared helpers (count from before the inline cutoff moved to 10%).
- A new helper goes into `include/ps2inline.h` or `include/vu0inline.h`, measured on more than one function: one instruction each, no register pins, no `"memory"` clobber.

### Stage 5: SDK range drafting (Complete, apart from four measured walls)

- Status 2026-11-15: `MultiplyUnsignedWide` (libgcc's `umul_ppmm`, one `multu`) landed in `ps2inline.h`; it gives retail's `multu`, `mfhi`, `mflo` in all four 64-bit division functions. `__divdi3` and `__udivdi3` match (the second only with `sony29-01`, now in `config/us/sony_gcc29_01.txt`): matched code 71.95% to 72.23%, 5586 to 5588 functions. `__moddi3` (7) and `__umoddi3` (4) keep an unused 0x20 of frame that nothing accesses; `__umoddi3`'s tail is a split epilogue (`func_0023D32C`).
- Eight SDK near misses ran as single waves: `func_002542B8` 1 (one rodata link word), `func_002358A0` 2, `sceMpegInit` 2, `func_00235780` 2 (with `sony29`), `func_002540B0` 6. Four of them end on an unfilled delay slot where retail filled it; the volatile-store-in-delay-slot wall of stage 2 is the likely common cause.
- Status 2026-11-16: seven more landed as single waves (`S5-<addr>`): `__ieee754_log`, `func_0024D5E8` (7,592 bytes, libmpeg PES header reader), `func_0024FC58`, `func_002358A0`, `func_002542B8`, `__moddi3`, `__umoddi3`. Matched code 72.23% to 73.31%, 5588 to 5594 functions. `__moddi3` and `__umoddi3` need `sony29-01` (the unused 0x20 frame goes away); `__umoddi3`'s split epilogue is a `merges.tsv` row; `func_0024D5E8` joins `sony_gcc29.txt`. `func_002358A0` was not the delay-slot wall: `return fixed >> 32` after merged `<< 32` tails lets gcc fill the `jr` slot (a single-instruction step); `(int)` of a long compiles to a two-instruction truncate and leaves the slot empty. `func_002542B8`'s one word was a second anonymous rodata table: copy the table from the existing `D_002AC838` global instead of a local initialiser. Also fixed: a statement swap from `make search` had broken `__udivdi3` (8); restored.
- Walls (measured, `config/us/blocker_notes.tsv`): `func_002540B0` (6), `sceMpegInit` (2), `func_00235780` (2), `func_0024C670` (12, plus a v0/v1 swap). Retail puts a constant-address store in a delay slot; Sony's gcc reorg never puts a volatile store there, a plain one folds to the `$at` form, and neither assembler swaps it in. Same class: `0x24C4B0`, `0x2539D0`.
- Open: `make unit UNIT=sdk` still reports `__udivdi3` from assembly (differs at +0x3ec) though `try.py` scores 0; it did so before this round.
- Left: nothing in the SDK range except the walls above and the libm drafts of stage 2.

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
