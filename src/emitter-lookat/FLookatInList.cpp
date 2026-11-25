#include "types.h"
// SPDX-License-Identifier: GPL-3.0-or-later
struct LOOKAT;
struct LOOKATOWNER { u8 unknown_0x0[0x90]; LOOKAT *plookatFirst; };
struct LOOKAT { int lookatk; u8 unknown_0x4[0x4]; LOOKATOWNER *powner; u8 unknown_0xC[0x4]; LOOKAT *plookatNext; };
extern "C" int FLookatInList(LOOKAT *plookat)
{
    for (LOOKAT *plookatCur = plookat->powner->plookatFirst; plookatCur != 0; plookatCur = plookatCur->plookatNext) {
        if (plookatCur == plookat) return 1;
    }
    return 0;
}
