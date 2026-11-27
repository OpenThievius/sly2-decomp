// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
void func_0020A518(STEPGUARD *owner, int value)
{
    unsigned count = owner->field_0xE94;
    if (count < 8) {
        owner->field_0xE98[count] = value;
        owner->field_0xE94 = count + 1;
    }
}
