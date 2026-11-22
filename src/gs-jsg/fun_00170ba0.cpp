// SPDX-License-Identifier: GPL-3.0-or-later
#include "script.h"
extern "C" {
void *PcmdAllocScript(SCRIPT *, int, int);
void func_00170BA0(SCRIPT *script, BYTES8 *payload) {
    PCMDPAYLOAD *command = (PCMDPAYLOAD *)PcmdAllocScript(script, 2, -1);
    command->payload = *payload;
}
}
