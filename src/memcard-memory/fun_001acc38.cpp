// SPDX-License-Identifier: GPL-3.0-or-later
#include "clock.h"
#include "memcardmenu.h"
extern "C" {
extern s8 B_002E65E0[];

void func_001ACC38(MEMCARDMENU *pmenu, s32 phase) {
    if (phase != pmenu->phase) {
        if (phase < 4) {
            if (phase >= 2) {
                u32 tableOffset = 0x8000;
                s8 *table = B_002E65E0 + tableOffset;
                *(s32 *)(table + 0x7D50) = 0;
            }
        }
        pmenu->phase = phase;
        pmenu->tPhase = g_2dded0.tReal;
    }
}

}
