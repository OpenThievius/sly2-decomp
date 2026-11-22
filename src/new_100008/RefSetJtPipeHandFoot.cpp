// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { char b[8]; };
extern "C" const AOT RO_002A3EF8;
extern "C" void SetJtPipeHandFoot(char *, QW, QW);
CRef RefSetJtPipeHandFoot(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3EF8;
    VECTOR a, b;
    RefSetArgsFromSplice(2, args, &aotyp, &a, &b);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    SetJtPipeHandFoot((char *)object + 0xF50, *(QW *)&a, *(QW *)&b);
    return refResult;
}
