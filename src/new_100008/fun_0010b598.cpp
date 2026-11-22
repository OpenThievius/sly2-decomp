// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
CRef RefSetArgsFromSplice(int cref, CRef *aref, const void *aotyp, ...);
extern "C" void bevy_player_p13_18df50(BASIC *, int);

extern "C" CRef func_0010B598(BASIC *object, int count, CRef *args)
{
    int aotyp = 0;
    int value;
    RefSetArgsFromSplice(1, args, &aotyp, &value);
    CRef refResult;
    refResult.SetTag(TAGK_Void);
    bevy_player_p13_18df50(object, value);
    return refResult;
}

