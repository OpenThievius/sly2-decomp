// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int GrficFromAlo(BASIC *, int);

extern "C" CRef RefCallGrficFromAlo(BASIC *object, int count, CRef *args)
{
    int aotyp = 0x1011;
    int grftak;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &grftak);
    refResult.SetS32(GrficFromAlo(object, grftak));
    return refResult;
}
