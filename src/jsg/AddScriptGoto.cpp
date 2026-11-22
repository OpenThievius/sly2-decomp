// SPDX-License-Identifier: GPL-3.0-or-later
#include "script.h"
extern "C" {
void *PcmdAllocScript(SCRIPT *, int, int);

void AddScriptGoto(f32 field_0x14, SCRIPT *script, int oid, int field_0x10) {
    PCMDGOTO *command = (PCMDGOTO *)PcmdAllocScript(script, 7, oid);
    command->field_0x14 = field_0x14;
    command->field_0x10 = field_0x10;
}
}
