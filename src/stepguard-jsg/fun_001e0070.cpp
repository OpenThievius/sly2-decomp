// SPDX-License-Identifier: GPL-3.0-or-later
#include "jsg.h"
void *memmove(void *, const void *, unsigned int);
extern "C" void func_001E0070(JSG *jsg, int signal)
{
    for (int index = 0; index < jsg->csignal; index++) {
        s32 *dst = &jsg->asignal[index];
        s32 *src = dst + 1;
        if (*dst == signal) {
            memmove(dst, src, (jsg->csignal - index) * 4 - 4);
            jsg->csignal -= 1;
            return;
        }
    }
}
