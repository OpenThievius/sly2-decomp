// SPDX-License-Identifier: GPL-3.0-or-later
// 0x1DFFE0 FUN_001dffe0
#include "jsg.h"

extern "C" void StopJsg(JSG *);
extern "C" void AddJsgContext(JSG *, int);

void ClearJsg(JSG *pjsg)
{
    StopJsg(pjsg);
    pjsg->phase = 0;
    AddJsgContext(pjsg, -1);
    pjsg->fPendingCut = 1;
}
