// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct RHYTHM;
extern "C" void ResetRhythmScore(RHYTHM *);

extern "C" CRef RefResetRhythmScore(RHYTHM *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    ResetRhythmScore(object);
    return refResult;
}
