/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct CFRAME {
    s32 refs;
};
struct CFRAMEPTR {
    struct CFRAME *pframe;
};

void CFrame_DeletingDestructor(struct CFRAME *pframe, s32 flags);
void __builtin_delete(void *pv);

/* CFramePtr destructor: drops the reference, deleting the frame at zero and the pointer itself when bit 0 of flags is set. */
void func_002572E0(struct CFRAMEPTR *pframeptr, s32 flags) {
    struct CFRAME *pframe;
    s32 refs;

    pframe = pframeptr->pframe;
    if (pframe != 0) {
        refs = pframe->refs - 1;
        pframe->refs = refs;
        if (refs == 0) {
            CFrame_DeletingDestructor(pframe, 3);
        }
    }
    if (flags & 1) {
        __builtin_delete(pframeptr);
    }
}
