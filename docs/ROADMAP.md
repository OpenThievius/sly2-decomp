# Roadmap

The one plan: where the project stands, what "100%" means, and the next steps in order. Live numbers:
[bytematch.dev](https://bytematch.dev/Blightwidow/sly2-decomp) and the README table. How each step was done and what was measured on
the way is in [ROADMAP_HISTORY.md](ROADMAP_HISTORY.md) (the former `ROADMAP.md` and `PATH_TO_100.md`, kept verbatim). The rules are in
AGENTS.md; the matching procedure in [AGENT_WORKFLOW.md](AGENT_WORKFLOW.md); what a port needs in [PORTING.md](PORTING.md).

Preservation is the priority. What helps a later port is additive (headers, typedefs, asserts, metadata, notes) and never changes
matched bytes or what counts as matched ([PRESERVATION_AND_PORT.md](PRESERVATION_AND_PORT.md) "The rule").

## Where we are (2026-11-21)

From `progress/us/report.json` and `progress/eu/report.json` on `main` (`a08128db`), `scripts/list_functions.py` and `config/`.
Numbers move; re-measure before each step.

- **Code: 79.65%** (927,380 of 1,164,348 bytes), 5,727 of 6,064 functions. The 812 permanent blockers (`config/us/blockers.tsv`: VU0,
  MMI, COP0, hand-written, remnants) stay original assembly and are left out of the totals, so this is the share of everything C
  can express.
- **Work queue:** 271 unmatched functions with a draft in `nonmatching/`, 14 without one (all SDK range). 244 of them are measured
  walls (`config/matching/walls.tsv`): not attempted again without an unlocking finding.
- **Data: 33.99%** (343,849 of 1,011,732 bytes). Ceiling about 49%: the irx and vutext regions are not game C.
- **PAL: 77.20%**, 5,627 functions: 100 functions do not reproduce PAL from the same C.
- **Whole files:** 199 of 209 proved (item 2).

## What "100%" means

| Target | Meaning | State |
| :--- | :--- | :--- |
| A. C-expressible code | every function outside the blockers scores 0 and `make elf` passes | 79.65% |
| B. Whole image | `make elf` reproduces retail byte for byte | holds (a gate, not work) |
| C. Data | data defined from C where a reader shows its type | 33.99%, ceiling about 49% |
| D. Source shape | one definition per type, real classes and virtuals, files as retail had them | items 1, 2, 7 |

Exact C of all code (blockers counted back in) tops out near 83%. The expected ceiling of A is in the 90s, not 100%: what stays is
measured walls, each with one line of semantics.

## Done

- The executable splits and rebuilds byte for byte from assembly plus the matched C (`make elf`); PAL is checked against the same C
  (`make pal`).
- One assembler for all game code: SN's `ps2eeas` with its short-loop constant changed from 6 to 5 (2026-11-05,
  [build/assembler.md](build/assembler.md)). The SDK range builds with Sony's gcc 2.9 (`config/us/sony_gcc29.txt`, libm with 991111-01).
  Per-function exceptions are documented in [contributing/exceptions.md](contributing/exceptions.md).
- Permanent blockers flagged (`make blockers`), remnants included (2026-11-09). Framed functions with at most 10% VU0, MMI and system
  instructions are an inline kind, counted as to-do and matched with the shared helpers of `include/ps2inline.h` and
  `include/vu0inline.h` (2026-11-11, cutoff 10% since 2026-11-12).
- Shared types in `include/`: fixed-width typedefs, `LO`/`SO`/`SLOTSO` as real C++ classes with virtuals, `SW`, `DL`, `XF`, `CRef`,
  `ALLOCREQ`, the player classes, `STEPGUARD`, `GOAL`, `CLONESET`, `TIMEDCALL`, `PHYS`.
- Whole files from the constructor list: 199 of 209 build whole; the whole file is the only record of its functions.
- Data from C: typed `.data` and `.rodata` groups, tables typed by hand from their readers.
- SDK range drafting complete apart from measured walls (path-to-100 stage 5); 14 SDK functions still have no draft.
- CI is sly1-decomp's (`checks`, `progress`); commit messages and cleanup rules are checked locally (`make commits`, `make cleanup`).

## Next

Order: shared types first (item 1), because every match landed on padded local structs adds to the later cost; then one source layout
(item 2) and the data build side (item 3); then the port-facing items (4, 7). Matching (item 5) runs only on a measured lever, not as
waves. Item numbers are stable: tools and docs cite them.

1. **Shared types** (In Progress). One definition per class in `include/`, typed from what retail's code does, field names keeping
   their `source:`. A field enters a header when a method of the class reads it, or two readers agree. Left: the goal subclasses,
   `GUARD`, the `CRef` remainder (195 files), the `aseg` segment type, 24 local `JT`-like structs, 9 Murray/Bentley copies, 48 guard
   layouts, 288 files with hand-written vtable calls. Editing `include/` changes the scorer fingerprint: do it between waves.
2. **Whole files** (In Progress). Left: `po_screen_210eb0`, `SyncVBlank_file`, `StartupJmt_file`, `PloFindSpawn_file` (one callee or
   global written with several types), `QueueSwCallback_file` and `PsoHitTestLineObjects_file` (compile to another size), and four
   files with per-function flag lists. Then the 826 low-confidence cuts inside a span, checked as item 3's first stage.
3. **Data from C** (In Progress). A global is defined in C only where its initial value reproduces retail's bytes at its address,
   typed (`// data-ok: typed from <reader>` for a word array over 64 elements). Left: 5 word arrays no reader types, 151 jump tables of
   unmatched functions, 6 SDK byte tables, 20 groups where Splat's labels split a word, `.bss`, and the list of defined globals
   feeding the report per global, as sly1-decomp does. Typed with the shared headers, not new per-file structs.
4. **Port-facing metadata, no code change** (Not Started). Depends on 1. Details and reasons in [PORTING.md](PORTING.md).
   - A layer column in `src/MANIFEST.tsv` and the registry: game logic, engine, platform (SDK range, GS, VIF and DMA, IOP, memory card,
     pad, VU microcode). The Sly 1 port keeps this list by hand (`libraries.tsv`).
   - Exports in sly1-decomp's schema, so the OpenThievius port tooling reads them unchanged: `config/us/functions.tsv`, the defined
     globals (`c_data.tsv`), symbols, the class tree, vtable layouts and struct offsets generated from the headers.
   - The addresses of every table of function pointers in data (vtables, callback and Splice binding tables): a port that maps
     retail's data must rewrite them.
   - One line of semantics per blocker and per shared inline helper, PS2 FPU behaviour noted where results depend on it.
5. **Matching on a measured lever only** (In Progress, procedure: [AGENT_WORKFLOW.md](AGENT_WORKFLOW.md)). Waves yield about 20
   bytes per claimed function; what moved the number was systematic unlocks (loop5, `-fmove-all-movables`, `function_flags.tsv`,
   the shared helpers). Group the drafts by wall class (`classify_diffs.py`), measure one lever per class against a control, land
   it, `rejudge.py` the affected drafts, and run a wave only on a class where a lever just landed. Check `walls.tsv` and
   `work/matching/runs.log` before any wave. Open threads from the path-to-100 stages:
   - Near misses: `StartLoadingLogo` (9, a high-part register tie), `powf` and the libm drafts.
   - Inline kind: `RenderGlobsetTree` (328, its `vcallms` and `cfc2.i` still inline asm), `func_001B8D30` (9), `func_001CC2E8` (4,
     needs a two-instruction `DotProductXy` with one user), `UpdateVehicle` (43), `UpdateGuardSensor` (26), `RefOpMult` (33).
   - Tail: `FireExplsExplso` (0x15C690) has no draft. What is left after that is a permanent wall: one line of semantics in
     `walls.tsv`, never equivalent C.
6. **Inline kind** (Complete, 2026-11-11; cutoff 10% since 2026-11-12). Matching what is left is item 5.
7. **Host-portable source, same bytes** (Not Started). Each change keeps `make elf` byte for byte and every score at 0; a port then
   swaps a header instead of patching game files. The Sly 1 port patches each of these by regex over sly1-decomp's text
   ([PORTING.md](PORTING.md) "What the Sly 1 port patches"). Counts are a rough grep over `src/` and `include/` on 2026-11-21.
   - **One prototype per function.** 94 names are declared with different argument counts in different units, and about 295 more
     only as `()` in C sources. Declarations move to shared headers; `make cleanup` reports a conflict in added code.
   - **No non-void function falling off its end.** A report from the host check below (`-Wreturn-type`); on the EE the caller reads
     whatever `$v0` held, on a host it is undefined.
   - **Named forms for EE-only idioms**, where the bytes stay identical: uncached and scratchpad addresses (`| 0x20000000`,
     `0x70000000`: 44 lines in 34 files) behind one macro; GCC 2.95's `>?` and `<?` (8 lines) and named return values (1) behind
     helpers; varargs that step 8-byte EE slots (3 files).
   - **Aligned vector globals** typed `QW` or `VECTOR` rather than `f32[4]`, so a host linker keeps their 16-byte alignment (the
     tie-break rule already prefers the type).
   - **Bare `long`** (642 lines): `s64` or `s32` as retail's code uses it.
   - **Members instead of raw offsets.** 1,594 reads at a raw offset in 465 files, 386 of them pointer reads (sly1-decomp: 269 and
     32). Under native 64-bit pointers (PORTING.md route A) every type takes the host's layout, so these, not the layouts, are the
     cost; it also settles `virtual` (55 files rely on gcc 2.95's vtable layout, which even a modern 32-bit compiler does not keep).
   - **An integer type for addresses** (In Progress): `sptr`/`uptr` in `include/types.h` since 2026-11-21, as sly1-decomp has,
     for the places where a pointer type would change retail's code. 285 casts of a pointer to a 32-bit integer in 167 files now
     use them (same types, `make elf` PASS, reports unchanged); with a port's 64-bit `sptr`/`uptr` the x86-64-only pointer-to-integer
     casts fall from 278 to 1 (`CloseFrame`, whose local `QW` clashes with `types.h`). Next: the integer fields and locals those
     values land in (214 x86-64 truncations with the 64-bit typedefs), and the 218 integer-to-pointer casts.
   - **A host syntax check that reports, never gates**: `clang -fsyntax-only` for i386 and x86-64 over `src/` with a shim header,
     writing a warnings report. Moved forward from "when a port starts": it measures the items above. First measurement
     (2026-11-21, [PORTING.md](PORTING.md) "Measured"): 278 pointer-to-integer and 224 integer-to-pointer casts only on x86-64.

## Cross-cutting

- `make pal` after each land; commit `config/eu/` and `progress/eu/report.json`. A function that no longer reproduces PAL is a finding.
- Before committing: `make check`, `make elf`, `make objdiff`, `make readme`. Run `make` with `PROGRESS=0`.
- Reservations: one comment per contributor on the coordination issue, at most 500 unfinished functions.
- Costs: `python3 scripts/cost_report.py` after each large step; append a dated row to `docs/costs.md`.

## When a port starts

- Reference C for functions that stay assembly, labelled "behaviour, not original", lives in the port's repository (or a
  `reference/` folder here), never in `src/` or the reports. An equivalence harness, if built, is optional tooling.
- The port's own work, platforms and the hand-off between the two repositories: [PORTING.md](PORTING.md).

## Not goals

The renderer, the audio engine, a platform layer and the port itself live in other projects. "Behaviourally equivalent" C is not a
match and does not go in `src/` or the reports.

## Unresolved questions

- Which "100%" is the headline: the report's matched code, every function with a draft scoring 0, or image bytes (already true)?
- Does the prototype check gate added code in `make cleanup`, or only report?
- Exports: sly1-decomp's schema exactly, or ours with an adapter in the port?
- Who writes the semantics lines for the 812 blockers: workers as they meet them, or one pass?
