// SPDX-License-Identifier: GPL-3.0-or-later
#include "clock.h"
#include "memcardmenu.h"
#include "memcard.h"
extern "C" {
extern SAVE B_002E65E0;

void func_001ACC38(MEMCARDMENU *pmenu, s32 phase) {
    if (phase != pmenu->phase) {
        if (phase < 4) {
            if (phase >= 2) {
                B_002E65E0.pslotCur = 0;
            }
        }
        pmenu->phase = phase;
        pmenu->tPhase = g_2dded0.tReal;
    }
}

}
