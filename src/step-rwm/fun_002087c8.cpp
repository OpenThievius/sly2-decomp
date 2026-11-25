// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
void func_002087C8(STEPGUARD *guard)
{
    SENSOR *sensor = guard->psensor;
    sensor->centry -= guard->csensed;
    guard->cgroup = 0;
    guard->csensed = 0;
}
