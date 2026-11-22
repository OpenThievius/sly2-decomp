// SPDX-License-Identifier: GPL-3.0-or-later
#include "attach.h"
extern "C" {
s32 func_00194640(ATTACH *pattach) {
    s32 result;
    s32 kind;

    kind = pattach->kind;
    switch (kind) {                              /* irregular */
    case 8:
        if ((u32) (pattach->field_0x0C - 9) < 2U) {
        case 12:
            return 1;
        }
        { result = 0; goto done; }
    default:
        { result = 0; goto done; }
    }
done:
    return result;
}

}
