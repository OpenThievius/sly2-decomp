// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
struct SENSORCHAIN {
    u8 unknown_0x0[0x10];
    s32 field_0x10;
};
struct SENSORHOLDER {
    u8 unknown_0x0[0xDC];
    SENSORCHAIN *pchain;
};
struct SENSOROWNER {
    u8 unknown_0x0[0xE8];
    SENSORHOLDER *pholder;
};
extern "C" s32 func_00259B18(SENSOROWNER *owner) {
    SENSORHOLDER *holder = owner->pholder;
    SENSORCHAIN *chain = 0;
    if (holder != 0) {
        chain = holder->pchain;
    }
    s32 result = 0;
    if (chain != 0) {
        result = chain->field_0x10;
    }
    return result;
}
