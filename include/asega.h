/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ASEGA, an animation handle (murray.h, sly.h, stepguard.h and wipe.h only forward-declare it), and ASEG, the animation it plays
   (slotso.h, sly.h forward-declare it), as far as the Murray carry code reads them. SetMurrayCarryState and UpdateMurrayCarry (tLocal), SetMurrayCarryState (paseg, tLength): the phase it keeps
   is tLocal / tLength. FillBlAmrsg_file reads tLocal at the same offset. C++ only. */
#ifndef SLY2_ASEGA_H
#define SLY2_ASEGA_H
#include "types.h"

struct ASEG {
    u8 unknown_0x0[0x74];
    /* 0x74 */ f32 tLength;
};

struct ASEGA {
    u8 unknown_0x0[0x14];
    /* 0x14 */ ASEG *paseg;
    u8 unknown_0x18[0x4];
    /* 0x1C */ f32 tLocal;
};
#endif
