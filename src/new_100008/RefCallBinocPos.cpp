// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int w[3]; };
extern "C" const AOT RO_002A3E20;
extern "C" void AddSeqRecordBinocPos(BASIC *, QW, QW, float);
CRef RefCallBinocPos(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3E20;
    VECTOR a, b;
    float c;
    RefSetArgsFromSplice(3, args, &aotyp, &a, &b, &c);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddSeqRecordBinocPos(object, *(QW *)&a, *(QW *)&b, c);
    return refResult;
}
