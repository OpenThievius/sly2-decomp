// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
GUARDANIM *PguardanimFind(STEPGUARD *owner, u64 key)
{
    int index = 0;
    int count = owner->canim;
    if (index < count) {
        GUARDANIM *anim = owner->aanim;
        do {
            index++;
            if (anim->grf == key) return anim;
            anim++;
        } while (index < count);
    }
    return 0;
}
