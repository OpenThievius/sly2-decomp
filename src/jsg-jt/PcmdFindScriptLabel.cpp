// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "script.h"
struct CMD : PCMD { u8 unknown_0x8[0x10]; CMD *next; };
extern "C" CMD *PcmdFindScriptLabel(SCRIPT *script, int label)
{
    VECTOR vector;
    CMD *cmd = (CMD *)script->slPcmd.pvFirst;
    while (cmd != 0) {
        if (cmd->type == 9 && cmd->oid == label)
            break;
        cmd = cmd->next;
    }
    return cmd;
}
