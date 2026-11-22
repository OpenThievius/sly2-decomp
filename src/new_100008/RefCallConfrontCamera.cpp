// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int v[5]; };
extern "C" const AOT RO_002A3DE0;
extern "C" void AddSeqRecordConfrontCamera(BASIC *, QW, QW, float, float, int);
CRef RefCallConfrontCamera(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3DE0;
    VECTOR v0, v1;
    float v2, v3;
    int v4;
    RefSetArgsFromSplice(5, args, &aotyp, &v0, &v1, &v2, &v3, &v4);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    AddSeqRecordConfrontCamera(object, *(QW *)&v0, *(QW *)&v1, v2, v3, v4);
    return refResult;
}
