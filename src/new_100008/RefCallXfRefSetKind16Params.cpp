// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { char b[24]; };
extern "C" const AOT RO_002A3FC0;
extern "C" void func_001F8BF0(BASIC *, int, QW, float, float, float, float);
CRef RefCallXfRefSetKind16Params(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3FC0;
    int v0;
    float v1, v2, v3, v4;
    VECTOR vec;
    RefSetArgsFromSplice(6, args, &aotyp, &v0, &v1, &v2, &v3, &v4, &vec);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    func_001F8BF0(object, v0, *(QW *)&vec, v1, v2, v3, v4);
    return refResult;
}
