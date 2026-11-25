// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" GUARDANIM *PguardanimFind(STEPGUARD *, u64);
extern "C" void ResetAnimref(GUARDANIM *, STEPGUARD *);
extern "C" GUARDANIM *PguardanimEnsure(STEPGUARD *guard, u64 key) {
    GUARDANIM *anim = PguardanimFind(guard, key);
    if (anim == 0) {
        GUARDANIM *added = &guard->aanim[guard->canim++];
        added->grf = key;
        anim = added;
    }
    ResetAnimref(anim, guard);
    return anim;
}
