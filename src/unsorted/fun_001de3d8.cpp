#include "types.h"
/* SPDX-License-Identifier: GPL-3.0-or-later */
struct S { u8 unknown_0x0[0x150]; unsigned count; int items[7]; };
extern "C" void func_001DE3D8(S* s, int v) { unsigned n = s->count; if (n < 7) { s->items[n] = v; s->count = n + 1; } }
