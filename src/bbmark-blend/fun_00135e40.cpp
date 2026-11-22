// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
extern "C" {
s32 func_001409B8(void);

s32 func_00135E40(BENTLEY *pbentley) {
    s32 result;

    result = func_001409B8();
    if (result == -1) {
        switch (pbentley->state) {
        case 1:
        case 5:
        case 0xE:
            return 1;
        default:
            return -1;
        }
    }
    return result;
}

}
