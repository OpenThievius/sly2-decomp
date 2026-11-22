/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "script.h"

void InitLo(struct SCRIPT *script);
void InitSl(struct SL *sl, s32 ibSle);

void InitScript(struct SCRIPT *script) {
    InitLo(script);
    InitSl(&script->slPcmd, 0x18);
}
