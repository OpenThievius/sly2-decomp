// SPDX-License-Identifier: GPL-3.0-or-later
#include "murray.h"
extern "C" {
s32 func_00143C78();

s32 NMurrayActionCategory(MURRAY *pmurray) {
    if (pmurray->field_0x204 != 0) {
        return 0;
    }
    if ((pmurray->field_0x13D8 == 1) || (pmurray->state == 0x14)) {
        return 0;
    }
    return func_00143C78();
}

}
