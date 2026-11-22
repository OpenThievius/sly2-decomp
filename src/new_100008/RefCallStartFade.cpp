// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct FADE;
extern "C" void StartFade(FADE *);

extern "C" CRef RefCallStartFade(FADE *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    StartFade(object);
    return refResult;
}
