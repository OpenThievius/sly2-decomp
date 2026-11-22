// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct BASIC;
extern "C" CRef *CRef_SetVector(CRef *, QW);
extern "C" QW PosAimAtPlayer(BASIC *, QW);
extern "C" CRef RefPosAimAtPlayer(BASIC *object, int count, CRef *args)
{
    int aotyp[1] = {2};
    VECTOR pos;
    CRef ref = RefSetArgsFromSplice(1, args, aotyp, &pos);
    CRef_SetVector(&ref, PosAimAtPlayer(object, *(QW *)&pos));
    return ref;
}
