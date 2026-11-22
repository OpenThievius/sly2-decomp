// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void CloneXfm(void *);

extern "C" void AttachFlat_Clone(ATTACHFLAT *attach)
{
    BYTES8 kept = attach->kept;
    CloneXfm(attach);
    attach->kept = kept;
}
