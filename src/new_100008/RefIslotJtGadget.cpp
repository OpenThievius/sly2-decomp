// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "jt.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int IslotJtGadget(JT *, int);

extern "C" CRef RefIslotJtGadget(JT *object, int count, CRef *args)
{
    int aotyp = 0x1049;
    int gadgetId;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &gadgetId);
    refResult.SetS32(IslotJtGadget(object, gadgetId));
    return refResult;
}
