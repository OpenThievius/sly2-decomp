/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

typedef struct CFRAME { s32 refCount; } CFRAME;
void CFrame_DeletingDestructor(CFRAME *, s32);

void CFramePtr_Assign(CFRAME **pptr, CFRAME *frame) {
    CFRAME *old;
    s32 count;

    if (frame != 0) {
        frame->refCount += 1;
    }
    old = *pptr;
    if (old != 0) {
        count = old->refCount - 1;
        old->refCount = count;
        if (count == 0) {
            CFrame_DeletingDestructor(old, 3);
        }
    }
    *pptr = frame;
}
