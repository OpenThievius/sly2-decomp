// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"

extern "C" GUARDANIM *PguardanimBestMatch(STEPGUARD *pguard, u64 grf);

// 0x209BC0 PguardanimCurrent
GUARDANIM *PguardanimCurrent(STEPGUARD *pstepguard)
{
    return PguardanimBestMatch(pstepguard, pstepguard->grfsgs);
}
