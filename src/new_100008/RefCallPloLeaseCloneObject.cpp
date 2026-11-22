// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "lo.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" LO *PloLeaseCloneObject(LO *, int);

extern "C" CRef RefCallPloLeaseCloneObject(LO *object, int count, CRef *args)
{
    CRef refResult = RefSetArgsFromSplice(0, args, 0);
    refResult.SetBasic(PloLeaseCloneObject(object, 0));
    return refResult;
}
