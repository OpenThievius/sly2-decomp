// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void CloneCrv(void *);

extern "C" void AttachCrv_Clone(ATTACHCRV *attach)
{
    BYTES8 kept = attach->kept;
    CloneCrv(attach);
    attach->kept = kept;
}
