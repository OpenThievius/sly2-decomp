// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "jt.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" int func_001424D0(JT *);

extern "C" CRef func_0010AB88(JT *object, int count, CRef *args)
{
    CRef refResult = RefSetArgsFromSplice(0, args, 0);
    refResult.SetBool(func_001424D0(object) != 0);
    return refResult;
}

