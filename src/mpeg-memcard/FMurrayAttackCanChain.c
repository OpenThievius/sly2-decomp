/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* The part of MURRAY (include/murray.h, C++ only) that the attack-chain test reads. */
struct MURRAYATTACKVIEW {
    u8 unknown_0x0[0x1810];
    s32 field_0x1810;
    u8 unknown_0x1814[0xC];
    s32 fCanChain;
    u8 unknown_0x1824[0xE8];
    void *field_0x190C;
};

s32 FMurrayAttackCanChain(struct MURRAYATTACKVIEW *pmurray) {
    if ((pmurray->field_0x190C != 0) || (pmurray->field_0x1810 != -1)) {
        return pmurray->fCanChain;
    }
    return 1;
}
