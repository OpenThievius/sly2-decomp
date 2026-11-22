// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
struct EXPL;
struct AOT { int v[6]; };
extern "C" void ExplodeExplParams__FP4EXPLUiP3ALOP6VECTORT3ff(EXPL *, unsigned, int, QW, QW, float, float);
extern const AOT RO_002A3C38;

CRef RefCallExplodeOvr(EXPL *expl, int count, CRef *args)
{
    AOT aotyp = RO_002A3C38;
    int flags;
    int palo;
    VECTOR vec;
    VECTOR origin;
    float scale;
    float radius;
    RefSetArgsFromSplice(6, args, &aotyp, &flags, &palo, &vec, &origin, &scale, &radius);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    ExplodeExplParams__FP4EXPLUiP3ALOP6VECTORT3ff(expl, flags, palo, *(QW *)&vec, *(QW *)&origin, scale, radius);
    return refResult;
}
