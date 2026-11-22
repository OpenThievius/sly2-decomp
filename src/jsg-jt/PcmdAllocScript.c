/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "script.h"
struct SLOTHEAP;

void AppendSlEntry(struct SL *sl, void *entry);
void *PvAllocSlotheapImpl(struct SLOTHEAP *slotheap);
extern struct SLOTHEAP B_003E1548;

void *PcmdAllocScript(struct SCRIPT *script, s32 type, s32 oid) {
    struct PCMD *command = (struct PCMD *)PvAllocSlotheapImpl(&B_003E1548);
    command->type = type;
    command->oid = oid;
    AppendSlEntry(&script->slPcmd, command);
    return command;
}
