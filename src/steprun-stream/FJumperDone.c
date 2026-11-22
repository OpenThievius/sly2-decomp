// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

s32 FJumperDone(struct JUMPER *pjumper) {
    return pjumper->state == 4;
}
