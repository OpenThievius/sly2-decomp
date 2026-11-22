// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
extern "C" {
void RecalcSwOxfFilterForObject(void *, SO *);
extern char B_003DD490;
void func_001F6918(SO *pso, s32 flag) {
    pso->grfso = (pso->grfso & ~(1UL << 26)) | ((u64)(flag & 1) << 26);
    RecalcSwOxfFilterForObject(&B_003DD490, pso);
}
}
