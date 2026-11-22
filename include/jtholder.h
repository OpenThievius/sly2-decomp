/* SPDX-License-Identifier: GPL-3.0-or-later */
/* JTHOLDER: the record bevy_player_p25_1371c8 and bevy_player_p25_137218 take, whose first word is the player (a JT: both read
   JT fields through it, 0x1030 and 0x10DC, and the first calls JT slot 88). C and C++. */
#ifndef SLY2_JTHOLDER_H
#define SLY2_JTHOLDER_H
#ifdef __cplusplus
#include "jt.h"
struct JTHOLDER {
    /* 0x0 */ JT *pjt;
};
#else
#include "jtview.h"
struct JTHOLDER {
    /* 0x0 */ struct JTVIEW *pjt;
};
#endif
#endif
