// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jsg.h"
extern "C" int FSggHasAlarm(JSG *sgg, int alarm)
{
    int index;
    for (index = 0; index < sgg->csignal; index++) {
        if (sgg->asignal[index] == alarm)
            return 1;
    }
    return 0;
}
