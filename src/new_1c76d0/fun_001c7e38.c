/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* C view of DPRIZE (include/dprize.h, C++ only): InitDprize starts it, field_0x1DC is its word at 0x1DC */
struct DPRIZEVIEW {
    u8 unknown_0x0[0x1DC];
    f32 field_0x1DC;
};

void InitDprize(struct DPRIZEVIEW *pdprize);

void func_001C7E38(struct DPRIZEVIEW *pdprize) {
    InitDprize(pdprize);
    pdprize->field_0x1DC = 50.0f;
}
