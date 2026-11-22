/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
s32 GsGetIMR();
s32 GsPutIMR(s32 mask);
s32 sceGsPutIMR(s32 mask) {
    s32 previous;
    previous = GsGetIMR();
    GsPutIMR(mask);
    return previous;
}
}
