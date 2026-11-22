// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "lo.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);

struct VT { short delta; short index; void (*fn)(void *, int); };

CRef RefCallSlot2D0(BASIC *object, int count, CRef *args)
{
    int aotyp = 0;
    int arg;
    RefSetArgsFromSplice(1, args, &aotyp, &arg);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    VT *vt = *(VT **)((char *)object + 0xC);
    VT *slot = (VT *)((char *)vt + 0x2D0);
    slot->fn((char *)object + slot->delta, arg);
    return refResult;
}
