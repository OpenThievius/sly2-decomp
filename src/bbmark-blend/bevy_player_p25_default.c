/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* what bevy_player_p25_default fills: a state number and a second word it sets to -1 (one function, no reader) */
struct BEVYSTATE {
    /* 0x0 */ s32 state;
    /* 0x4 */ s32 field_0x4;
};

void bevy_player_p25_default(struct BEVYSTATE *pbevystate, s32 state) {
    pbevystate->state = state;
    pbevystate->field_0x4 = -1;
}
