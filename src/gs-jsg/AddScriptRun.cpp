// SPDX-License-Identifier: GPL-3.0-or-later
#include "script.h"
extern "C" {
void *PcmdAllocScript(SCRIPT *, int, int);
void AddScriptRun(SCRIPT *script, int oid, int field_0x8, int field_0xC) {
    PCMDRUN *command = (PCMDRUN *)PcmdAllocScript(script, 6, oid);
    command->field_0x8 = field_0x8;
    command->field_0xC = field_0xC;
}
}
