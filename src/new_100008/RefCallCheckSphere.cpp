// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int v[2]; };
extern "C" const AOT RO_002A3BB8;
extern "C" int func_00227D20(BASIC *, QW, float);
CRef RefCallCheckSphere(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3BB8;
    VECTOR vec;
    float radius;
    CRef ref = RefSetArgsFromSplice(2, args, &aotyp, &vec, &radius);
    int hit = func_00227D20(object, *(QW *)&vec, radius);
    ref.SetBool(hit != 0);
    return ref;
}
