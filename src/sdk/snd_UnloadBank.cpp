// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
extern "C" {
int snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(int, int, char *, void (*)(int, u64), u64);
int snd_UnloadBank(int bank) {
    return snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(6, 4, (char *)&bank, 0, 0);
}
}
