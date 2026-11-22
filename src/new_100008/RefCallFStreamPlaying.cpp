// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
struct SND;
extern "C" int FStreamPlaying(SND *, int);

extern "C" CRef RefCallFStreamPlaying(SND *object, int count, CRef *args)
{
    int aotyp = 0x10;
    int id;
    CRef refResult = RefSetArgsFromSplice(1, args, &aotyp, &id);
    refResult.SetBool(FStreamPlaying(object, id) != 0);
    return refResult;
}
