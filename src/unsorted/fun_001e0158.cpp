#include "types.h"
/* SPDX-License-Identifier: GPL-3.0-or-later */
struct T { int kind; };
struct U { u8 unknown_0x0[0x18]; s32 v18; u8 unknown_0x1C[0x14]; T* t; };
struct O { u8 unknown_0x0[0x68]; U* u; };
extern "C" void func_001E0158(O* o, int v) { U* u = o->u; if (u) { if (u->t->kind == 9) u->v18 = v; } }
