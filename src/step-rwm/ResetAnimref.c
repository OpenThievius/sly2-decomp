/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guard.h"

void func_0020C030(void *pjumpanim);
void func_0020CA20(void *pdiranims);

void ResetAnimref(struct ANIMREF *ref) {
    s32 kind = ref->kind;
    if (kind != 2) {
        if (kind == 3) {
            func_0020CA20(ref->pdata);
            ref->pdata = 0;
        }
    } else {
        func_0020C030(ref->pdata);
        ref->pdata = 0;
    }
    ref->oid = -1;
    ref->kind = -1;
}
