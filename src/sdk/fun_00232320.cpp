/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
void snd_SendIOPCommandNoWait(int command, int size, char *data, void (*callback)(int, u64), u64 argument);
extern "C" {
void func_00232320(char *command, void (*callback)(int, u64), u64 argument) {
    snd_SendIOPCommandNoWait(0x5C, 0x30, command, callback, argument);
}
}
