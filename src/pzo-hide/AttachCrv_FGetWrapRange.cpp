// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" {
f32 SMaxCrv(void *);
f32 SMinCrv(void *);

s32 AttachCrv_FGetWrapRange(ATTACHCRV *attach, f32 *range)
{
    s32 result;
    if (attach->closed == 0) {
        result = 0;
        goto done;
    }
    range[0] = SMinCrv(attach);
    range[1] = SMaxCrv(attach);
    result = 1;
done:
    return result;
}
}
