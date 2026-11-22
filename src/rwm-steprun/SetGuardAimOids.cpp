// SPDX-License-Identifier: GPL-3.0-or-later
// 0x20AF28
#include "guard.h"

void SetGuardAimOids(AIMSTATE *paim, int oidA, int oidB, int oidLabel)
{
    paim->oidA = oidA;
    paim->oidB = oidB;
    paim->oidLabel = oidLabel;
}
