// SPDX-License-Identifier: GPL-3.0-or-later
#include "subtitle.h"

extern "C" {
Color4 func_002275B8(int colorKind);

void func_00227788(SUBTITLE *psubtitle) {
    psubtitle->sid = -1;
    psubtitle->color = func_002275B8(-1);
    psubtitle->grf = 0;
}
}
