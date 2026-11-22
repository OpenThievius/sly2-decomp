// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct AOT { int w[3]; };
extern "C" BASIC *SpawnSwHitFx(BASIC *, int, QW, int);
extern const AOT RO_002A3F20;
CRef func_0010BFF8(BASIC *object, int count, CRef *args)
{
    AOT aotyp = RO_002A3F20;
    int a, c;
    VECTOR vec;
    CRef ref = RefSetArgsFromSplice(3, args, &aotyp, &a, &vec, &c);
    ref.SetBasic(SpawnSwHitFx(object, a, *(QW *)&vec, c));
    return ref;
}
