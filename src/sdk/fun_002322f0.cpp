/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
void snd_SendIOPCommandNoWait(int command, int size, char *data, void (*callback)(int, u64), u64 argument);
extern "C" {
void func_002322F0(char *command) {
    snd_SendIOPCommandNoWait(0x5C, 0x30, command, 0, 0);
}
}
