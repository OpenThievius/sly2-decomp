// SPDX-License-Identifier: GPL-3.0-or-later
#include "epsel.h"
extern "C" {
extern int *D_002BE080[];
extern int *D_002BE1B8[];
s32 LabelFromEpselMode(EPSEL *epsel) {
    s32 mode = epsel->mode;
    if (mode == -1) return -1;
    if (mode == 8) {
        s32 sub = epsel->sub;
        if (sub != -1)
            return D_002BE1B8[epsel->field_0x128][sub];
    }
    return D_002BE080[epsel->episode][epsel->mode];
}
}
