// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct MGR;
extern "C" float FFindLevel(MGR *, int);

extern "C" CRef RefCallDtStream(MGR *object, int count, CRef *args)
{
    int aotyp = 0x10;
    int id;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &id);
    refResult.SetF32(FFindLevel(object, id));
    return refResult;
}

