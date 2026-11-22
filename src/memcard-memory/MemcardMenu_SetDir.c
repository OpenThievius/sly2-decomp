/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "memcardmenu.h"

extern f32 g_2ddf0c;

void MemcardMenu_SetDir(MEMCARDMENU *pmenu, s32 dir) {
    if (dir != pmenu->dir) {
        pmenu->dir = dir;
        pmenu->tDir = g_2ddf0c;
    }
}
