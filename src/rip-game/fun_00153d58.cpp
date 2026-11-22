// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "lo.h"
#include "sw.h"
extern "C" {
void InitXfm();
void func_001A6CA8(LO *, s32);
void func_00153D58(LO *lo) {
    InitXfm();
    func_001A6CA8(lo, 1);
    u32 flags = lo->grfSw;
    if ((flags ^ 1) & 1) {
        lo->pgrfentry->grf |= 2;
        return;
    }
    lo->grfSw = flags | 2;
}
}
