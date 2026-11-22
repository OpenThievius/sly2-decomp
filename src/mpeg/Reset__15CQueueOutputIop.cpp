// SPDX-License-Identifier: GPL-3.0-or-later
// 0x1B2A80 CQueueOutputIop::Reset
#include "cmpeg.h"
void CQueueOutputIop::Reset()
{
    cbFree = cbBuffer;
    cbQueued = 0;
    ibRead = 0;
    ibWrite = 0;
    field_0x2C = 0;
}
