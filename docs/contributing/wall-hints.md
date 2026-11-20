# Hints for the walls

Written 2026-11-20 after wave Z29. These are **hypotheses to test, not findings**: a lever becomes a finding only when it takes a function of
the class to 0 against a control (`config/matching/walls.tsv`, `unlock` column; AGENTS.md "Never attempt a walled function"). Use this page to
pick what to try first when a wave on walls is unlocked; `claim.py init --unlock '<finding>'` queues them.

## Tie walls (102)

Levers that took a near miss to 0 or closer in waves Z23 to Z29 (details in matching.md, "More fixes from 2026-11-20"):

- **`T *const` on a spilled pointer parameter.** The const marks the spill slot as unchanging, so sched2 no longer orders its reload after stores
  through another pointer (`LoadMovieCharacter`, 17 to 5, found with the sched2 dump). Try on scheduling ties where a reload or load sits on the
  wrong side of a store: `scePadPortOpen`, `UpdateGuardSensor`, `func_0023AAF0`.
- **A loop in a `do { } while (0)` statement macro.** A real loop level (allocator weights) and a loop note (scheduling barrier in GCC 2.95).
  Try where a store, `li` or address computation lands one slot early or late next to a loop (`func_0023B728`, `func_001A4AD8`). Only where the
  original plausibly had the macro.
- **A local, a parameter order or a shared counter that changes allocator priority or hash order.** GCSE PRE creates registers in hash-bucket
  order and the hash of `ibatch+1` depends on the counter's register; an inline's first parameter decides which global is hoisted first
  (`LoadMovieCharacter`, `func_001A4AD8`). Try where the note says two registers swap at the same live length or priority.
- **A `goto` to a label instead of `break`** keeps the loop-head test, so the loop gets its `.p2align` nop (`UpdateAsegaIeaCur`). Try on backward
  searches that are one nop or one compare off. `!(a <= b)` folds to `c.lt.s` under `-ffast-math`: write the positive `<=` that exits the loop.
- **A typed local for a literal threshold.** GCC 2.95 folds a literal into `sltiu`; retail's `sltu v0, 0xFE, alpha` means a variable
  (`FillScreenRect`, exceptions.md). Only where retail shows the register compare.
- **A constant with life 1 in a long loop** is rejected by loop.c ("savings 1 not desirable"); it moves a constant of life 2 or more.
  `-fmove-all-movables` fixes it but only as a file's flag, and breaks other loops in `LoadMovieCharacter`.
- **Diagnose before each run**: `sched1.py`, `globalalloc.py`, `regalloc.py` and the `-dL`/`-dG` dumps say which of priority, alias set or
  hoisting decides. Reordering statements is not a lever.

## "Exhausted" walls (90)

`classify_walls.py` labels these from run counts, which is unreliable: `UpdateAsegaIeaCur` (289 logged runs) and `FillScreenRect` (183) matched
once a structural change was found with the dumps. Re-triage them with the list above: one worker per function, a bound of 6 to 12 runs, no
off-log compiles, the ones at score 30 or lower first. A new reading of retail's block structure (a type, a field, an inline, a callee
signature) is the unlock the walls name.

## Toolchain walls (12)

- `-fno-gcse` (`GetXfLocalRateMatrix`): the whole-file `-fmove-all-movables` mechanism (`make_whole_files.py`, exceptions.md) is the model for a
  whole-file `-fno-gcse` flag. Needs a ruling and a measured control (precedent `0x13AC18`).
- Delay-slot fill (`func_0024C670`, `func_00252148`): needs an assembler or compiler change measured on two functions
  (docs/build/assembler.md). A large job; do not start it for one function.

## Helper walls

A shared helper in `include/ps2inline.h` or `vu0inline.h` needs two measured users. `RefOpMult` reads a float straight into a QW register with
one `lw` (no allowed helper does): survey the other unmatched functions for the same `lw` into a quadword before proposing a helper.

## Hand-written assembly (`memset`, `memcpy`)

Nothing to try. Open decision: a manual-override file next to `handwritten_asm.txt` for functions the detector misses.
