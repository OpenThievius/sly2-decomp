# Porting

What a native PC port of Sly 2 needs from this repository, what the Sly 1 port teaches, and who does what. The port itself lives
in another repository; this one stays a byte-matching decompilation ([PRESERVATION_AND_PORT.md](PRESERVATION_AND_PORT.md) "The
rule"). Our side of the work is in [ROADMAP.md](ROADMAP.md) items 4 and 7.

Written 2026-11-21 from a reading of OpenThievius's `wip/native-sly-port` branch (commit `612bc16`, AGPL-3.0-or-later) and a grep of
our `src/` and `include/`. Facts only: no code from that branch is copied here.

## The rule, restated

- Everything that helps a port here is additive: headers, typedefs, asserts, metadata, notes. It never changes matched bytes or what
  counts as matched.
- No "equivalent C" in `src/` or the reports. Host replacements for blockers, inline helpers and platform calls live in the port.
- The port reads this repository read-only and keeps its generated copies in its own build tree.

## How the Sly 1 port works

[OpenThievius](https://github.com/OpenThievius/OpenThievius) builds sly1-decomp (100% of code matched) into a native program,
following OpenRAC's architecture. No emulator, no model of the EE, VU, VIF, DMA or GS as the gameplay path.

| Part | What it does |
| :--- | :--- |
| Build | Compiles sly1-decomp's matched C and C++ directly for 32-bit Linux (i386), through a small ABI header that replaces the decomp's `common.h` (fixed-width typedefs, `mode(TI)` as a 16-byte vector). The decomp checkout is never edited; a staging step copies and patches it. |
| Memory | Maps retail's ELF data at its PS2 addresses, so pointers stay 32-bit and every struct offset stays retail's. Function addresses stored in that data are rewritten to the native functions. Objects are linked by retail address from `config/us/functions.tsv` and `c_data.tsv`. |
| Platform calls | About 30 kernel, IOP, CD, DMA, semaphore and thread entry points replaced by host services, listed by hand in `libraries.tsv`. |
| Backfills | 334 port-only functions (`port/game/sly1-us/hand/`) for what the matched C cannot run as is. Never counted as matching. |
| Rendering | OpenRAC's `DirectRenderer` draws the GIF packets the game emits: 2D works (menus, the memory-card screen). 3D, which goes through VU1 microcode, is unsolved. |
| Status | Not playable. Boots to the memory-card prompt; the intro movie plays only through an opt-in FFmpeg diagnostic; the world renders black. |

### What the Sly 1 port patches

`port/tools/compile_decomp_host32.py` (5,824 lines, 62 rewrites) patches sly1-decomp's text before compiling it, each rewrite keyed
to a file and failing when the text drifts. None of it carries over to Sly 2. Its classes, and how many sites of each we have:

| Class | What breaks on a host | Sly 1 port's fix | Ours (rough grep, 2026-11-21) |
| :--- | :--- | :--- | :--- |
| Wrong prototypes | A callee declared with fewer or other arguments than retail passes: MIPS leaves them in registers, i386 does not | rewrite declarations and calls (`forward_*_arguments`) | 94 names with conflicting argument counts; about 295 more declared only as `()` in C |
| Aggregates by value | 128-bit matrices or vectors passed by value: caller and callee disagree on i386 | pass by reference (`normalize_*_abi`) | to measure |
| Missing returns | A non-void function falls off its end; the EE caller reads leftover `$v0` | supply the return | to measure (`-Wreturn-type`) |
| Uncached aliases | `ptr \| 0x20000000` is a valid EE address, a wild one on a host | strip the alias | 44 lines in 34 files (`0x20000000`, `0x30000000`) plus 7 scratchpad `0x70000000` |
| GCC 2.95 extensions | `>?`, `<?`, named return values | lower to plain C++ | 8 lines; 1 |
| Varargs | the formatter steps 8-byte EE argument slots | change the stride | 3 files, 12 lines |
| Alignment | `f32 x[4]` globals rely on retail's address for 16-byte alignment | add `aligned(16)` | to measure |
| Inline asm | `sync`, `mfc0`, VU0 in function bodies | replace each string | none in game code: one place, `ps2inline.h` and `vu0inline.h` |
| 64-bit `long` | `long` is 64 bits on the EE, 32 on i386 and Windows | ABI header | 642 lines of bare `long` |

The last-but-one row is where we are already ahead: the shared helpers are one header a port replaces. ROADMAP item 7 does the same
for the other rows.

## What is different for Sly 2

- **Real C++ classes.** Sly 2's objects use gcc 2.95's layout: the vtable pointer at +0xC after the root's fields, 8-byte slots
  holding a delta and a function. Our headers declare them as real `virtual`s (55 files). A host compiler puts the pointer at offset
  0 with its own slots, so every field offset of these classes moves and retail's vtables in data stop matching the code, even on a
  32-bit host (measured below). Under route A this only matters where code or data relies on retail's offsets.
- **Vectors by value** in 128-bit registers (`VECTOR` arguments and returns), the aggregates-by-value row above.
- **More assembly left.** 812 permanent blockers (VU0, MMI, COP0, hand-written, remnants) and the unmatched functions need host
  versions in the port. The Sly 1 port needed 334 backfills even at 100% matched. Our `nonmatching/` drafts compile and are a
  starting point for the unmatched ones, unverified; the blockers need the semantics lines of ROADMAP item 4.
- **Rendering** goes through VU1 microcode in `.vutext` ([game/vu1-microcode.md](game/vu1-microcode.md)), like Sly 1's: the part the
  Sly 1 port has not solved.

## Platforms

The OpenThievius port targets Windows, macOS and Linux. Its only build that runs today is Linux i386: a freestanding launcher that
maps retail's data at fixed low addresses (`MAP_FIXED_NOREPLACE`) with its own `_start` and thread code. That model needs a 32-bit
process at those addresses:

- **Linux:** works today (i386).
- **Windows:** a 32-bit process under WoW64 could, with a Windows loader and threads written for it.
- **macOS:** cannot. macOS has not run 32-bit processes since 10.15, and Apple Silicon has no 32-bit mode.

So "multi-platform" needs a 64-bit build. There are two routes:

| Route | How | Who does it |
| :--- | :--- | :--- |
| A. Native 64-bit pointers | the decompiled source compiled as an ordinary 64-bit program; host layouts, host vtables | the source is typed until nothing depends on retail's offsets |
| B. 32-bit game pointers in a 64-bit program | game memory is one 4 GB reservation whose offsets are the PS2's addresses; a tool rewrites every dereference | OpenRAC (`port/tools/hostgen`, after OpenGOAL): Ratchet & Clank and Going Commando ship this way on Windows, macOS, Linux and Android |

Route B keeps retail's layouts and every console habit (raw offsets, pointers in `int`s, uncached aliases), but hostgen reads C
only. Sly 1's decompilation and ours are mostly C++ (classes, virtuals, constructors and destructors), which is why the Sly 1 port
compiles the source directly instead. Route B for either Sly would first need hostgen to read C++.

## Measured: how far each source is from route A (2026-11-21)

`clang -fsyntax-only` over every unit of `src/`, once for i386 (4-byte pointers, the control) and once for x86-64, diagnostics
deduplicated by file and line; what appears only on x86-64 is the pointer-width debt. Plus source patterns no compiler flags. The
script is a scratch tool (not in the repository); the regular expressions are rough and can over- or under-count.

| | sly1-decomp `8f7a85a` | sly2-decomp `a08128db` |
| :--- | ---: | ---: |
| Units compiled | 574 | 4,707 |
| Code in C | 100% | 79.65% (812 blockers stay assembly) |
| Data defined in C | 99.97% | 33.99% |
| x86-64 only: pointer cast to a smaller integer | 842 sites, 77 files | 278 sites, 168 files |
| x86-64 only: integer cast to a pointer | 421, 72 | 224, 147 |
| x86-64 only: 64-bit value shortened to 32 | 46, 26 | 58, 39 |
| Layout checks failing on x86-64 | 223 of 293 | 313 of about 330 |
| Layout checks failing on a modern i386 compiler | 32 (4 headers) | 63 (`LO`, `SO`, `SLOTSO`, `SW`, `PO`, `STEPGUARD`: the vtable pointer moves to offset 0) |
| Reads at a raw offset `*(T *)(p + 0x..)` | 269 sites, 76 files | 1,594 sites, 465 files |
| Pointers read at a raw offset `*(T **)(p + 0x..)` | 32, 13 | 386, 200 |
| Addresses cast to `int`/`u32` | 411, 110 | 220, 159 |
| Uncached or scratchpad aliases | 82, 33 | 56, 37 |
| An integer type for "holds an address" | `sptr`/`uptr` (include/common.h) | none (`sptr`/`uptr` added after this measurement, ROADMAP item 7) |

Our layout checks only compile for the PS2 (`#if defined(__mips__)`); they were measured with `offsetof` in a scratch copy of
`include/`. Not counted anywhere: `int` fields and padding that hold pointers without a cast, which no compiler sees.

What the numbers say:

- **A failing layout check is not the cost.** Under route A every type takes the host's layout; that only breaks code or data that
  assumes retail's offsets. The cost is the rows below it: raw-offset reads, addresses in integers, and data still in assembly
  (its pointers are 32-bit words at retail's addresses).
- **Sly 1 is close to route A.** Its code and data are in C, about 1,300 compiler-flagged sites and 269 raw-offset reads remain,
  and sly1-decomp already prepared for it: `sptr`/`uptr` ("a port to 64-bit pointers changes only those two lines", its
  docs/PORTING.md) and `tools/modern_check.py`, which keeps a modern compiler's errors from coming back.
- **Sly 2 is further.** Fewer compiler-flagged casts, but six times the raw-offset reads, twelve times the pointer reads at an
  offset, two thirds of the data still assembly, and the 812 blockers.
- **The 32-bit shortcut does not hold for Sly 2's classes.** Even a modern 32-bit compiler moves the vtable pointer of 63 checked
  fields: retail's layout survives only with gcc 2.95's ABI.

## Recommended route: A, for both games

- **Sly 1, now.** The OpenThievius pipeline already compiles the decompiled source directly; going from i386 to x86-64 continues it:
  fix the flagged sites (mostly by typing them `sptr`/`uptr` or as real pointers), drop the mapping of retail's data, and the
  32-bit-only parts (the fixed mapping, the freestanding Linux launcher) go. Route B would mean dropping that pipeline for a tool
  that cannot read its C++.
- **Sly 2, as the roadmap gets there.** Route A's prerequisites are this repository's ROADMAP items 1 (shared types: members instead
  of raw offsets), 3 (data from C) and 7 (host-portable source), all of which keep the bytes. With classes compiled natively and
  nothing reading them at retail's offsets, the `virtual` layout question goes away.
- **What route A cannot avoid:** host versions of every blocker and inline helper, and assets converted at extraction where the game
  loads disc data containing 32-bit pointers (not yet checked: whether Sly 2's level loaders read field by field or relocate raw
  blocks).

## On our side

In ROADMAP order; each keeps `make elf` byte for byte.

1. **Shared types** (item 1): one definition per class, so a port fixes a layout once.
2. **Port-facing metadata** (item 4): a layer column (platform against game), exports in sly1-decomp's schema
   (`config/us/functions.tsv`, `c_data.tsv`, symbols, class tree, vtable layouts, struct offsets), the addresses of every table of
   function pointers in data, and one line of semantics per blocker and per shared helper.
3. **Host-portable source** (item 7): one prototype per function, named forms for EE-only idioms, typed vector globals, `s64`/`s32`
   for bare `long`, members instead of raw offsets, `sptr`/`uptr` for addresses kept in integers, and the host syntax
   check that reports them.
4. **Layout asserts** in the headers ([PRESERVATION_AND_PORT.md](PRESERVATION_AND_PORT.md) item 3): on a host build they list
   every type that moves.

## On the port's side

For OpenThievius, or whichever repository hosts the Sly 2 port:

- **A Sly 2 game alongside Sly 1:** `games/sly2/game.json`, `port/game/sly2-us/` with its own `hostgen.json`, `libraries.tsv` and
  backfills, and a source setting for this checkout. Today the tools, macros and paths are Sly 1 by name (`sly1.py`, `SLY1_*`,
  `OPENTHIEVIUS_SOURCE_SLY1`).
- **No text patches for Sly 2.** Host fixes come from header shims on the include path or go upstream here as same-bytes changes.
- **Host versions of `ps2inline.h` and `vu0inline.h`**, picked by include-path order, one host body per helper.
- **Route A, 64-bit**, for Sly 1 first (the section above).

## Licence and sourcing

- This repository is GPL-3.0-or-later; OpenThievius is AGPL-3.0-or-later. GPL-3.0 code may be combined into an AGPL-3.0 program
  (section 13 of each), so the port can build our source. The reverse is not true: code from the port does not come back here
  unless its authors license it GPL-compatibly.
- OpenThievius's sourcing policy allows its own and OpenRAC's work only; it would need to name this repository as a source.
- AGENTS.md "Rules" still holds here: nothing from the port's game research enters this repository without its licence permitting
  it and an entry in THIRD_PARTY_NOTICES.md.

## Open questions

- Do Sly 2's level loaders relocate raw blocks with 32-bit pointers, or read field by field? (Decides how much the extractor must
  convert under route A.)
- Do we add `sptr`/`uptr` to `include/types.h`, as sly1-decomp did?
- Exports in sly1-decomp's schema exactly, or ours with an adapter?
- Where reference C for blockers lives: the port's repository, or a `reference/` folder here?
