// SPDX-License-Identifier: GPL-3.0-or-later
#include "rip.h"
extern "C" {
extern QW D_002BBB50;

/* a MATCH keeps two floats and a word in the RIP's gap at 0x20 to 0x2F (UpdateMatch reads them too): the words past 0x20 */
struct MATCHWORDS {
    u8 unknown_0x0[0x24];
    f32 field_0x24; /* 1.0 minus the float of 0x20 */
    s32 field_0x28;
};

void InitMatch__FP5MATCHP6VECTORfP2SO(RIP *match, QW pos, float fraction, SO *psoTouch) {
    InitRip__FP3RIPP6VECTORfP2SO(match, pos, fraction, psoTouch);
    match->field_0x30 = D_002BBB50;
    ((MATCHWORDS *)match)->field_0x28 = 0;
    match->field_0x20 = fraction;
    ((MATCHWORDS *)match)->field_0x24 = 1.0f - fraction;
}

}
