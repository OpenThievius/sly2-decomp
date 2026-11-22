// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" BASIC *EnsureLeasedObject(BASIC *);

extern "C" CRef RefCallEnsureLeasedObject(BASIC *object, int count, CRef *args)
{
    CRef refResult = RefSetArgsFromSplice(0, args, 0);
    refResult.SetBasic(EnsureLeasedObject(object));
    return refResult;
}

