// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"

extern "C" void func_001A2BD0(int);
extern "C" void RequestTransition(SW *, int, int, int, int, int);
extern "C" SW B_003DD490;

/* the language menu: SelectLanguage reads the chosen language from it */
struct LANGUAGEMENU {
    u8 unknown_0x0[8];
    s32 ilanguage;
};

void SelectLanguage(LANGUAGEMENU *menu)
{
    func_001A2BD0(menu->ilanguage);
    RequestTransition(&B_003DD490, 0, 0x189, -1, 1, -1);
}
