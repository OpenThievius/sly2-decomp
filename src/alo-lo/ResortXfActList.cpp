/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "act.h"
struct ALO;
void InvalidateXfSegment(ALO *, XF *);
void ResortXfActList(ALO *alo, XF *xf)
{
    ACT *acts[16];
    int count = 0;
    ACT *act0 = xf->pactFirst;
    while (act0) {
        acts[count++] = act0;
        act0 = act0->pactNext;
    }
    ACT *oldTop = xf->pactFirst;
    xf->pactFirst = 0;
    for (count--; count >= 0; count--) {
        ACT *act = acts[count];
        ACT **link = &xf->pactFirst;
        ACT *cur = xf->pactFirst;
        while (cur) {
            if (!(cur->priority > act->priority)) break;
            link = &cur->pactNext;
            cur = cur->pactNext;
        }
        act->pactNext = *link;
        *link = act;
    }
    if (xf->pactFirst != oldTop) {
        InvalidateXfSegment(alo, xf);
        if (oldTop) {
            ACTVT *vtOld = (ACTVT *)oldTop->vtable;
            vtOld->slot2.fn((char *)oldTop + vtOld->slot2.delta);
        }
        if (xf->pactFirst) {
            ACTVT *vtNew = (ACTVT *)xf->pactFirst->vtable;
            vtNew->slot1.fn((char *)xf->pactFirst + vtNew->slot1.delta);
        }
    } else if (oldTop) {
        ACTVT *vtOld = (ACTVT *)oldTop->vtable;
        vtOld->slot3.fn((char *)oldTop + vtOld->slot3.delta);
    }
}
