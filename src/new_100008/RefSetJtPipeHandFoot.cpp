// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "jt.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct AOT { int v[2]; };
extern "C" const AOT RO_002A3EF8;
extern "C" void SetJtPipeHandFoot(void *, QW, QW);

CRef RefSetJtPipeHandFoot(JT *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3EF8;
    VECTOR foot, hand;
    RefSetArgsFromSplice(2, args, &aotyp, &foot, &hand);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetJtPipeHandFoot(object->PvPipe(), *(QW *)&foot, *(QW *)&hand);
    return refResult;
}
