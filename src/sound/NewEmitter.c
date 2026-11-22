/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void InitAmb(void *pamb, s32 sfxid);
void *PvAllocAmb(s32 cb);

void NewEmitter(s32 sfxid)
{
    InitAmb(PvAllocAmb(0x70), sfxid);
}
