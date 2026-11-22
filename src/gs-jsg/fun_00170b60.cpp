// SPDX-License-Identifier: GPL-3.0-or-later
#include "script.h"
extern "C" {
/* 0x170B60: allocate a 0x10-byte command (type 1) and copy the 8-byte payload into its upper half */
void *PcmdAllocScript(SCRIPT *, int, int);
void func_00170B60(SCRIPT *script, const BYTES8 *payload) {
    PCMDPAYLOAD *command = (PCMDPAYLOAD *)PcmdAllocScript(script, 1, -1);
    command->payload = *payload;
}
}
