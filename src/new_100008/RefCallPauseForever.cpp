// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct EMITTER;
void PauseEmitterIndefinite(EMITTER *);

extern "C" CRef func_00105A00(EMITTER *object, int count, CRef *args)
{
    RefSetArgsFromSplice(0, args, 0);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    PauseEmitterIndefinite(object);
    return refResult;
}
