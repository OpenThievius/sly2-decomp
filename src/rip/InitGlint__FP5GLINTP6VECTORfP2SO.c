/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rip.h"

extern QW D_002C1F90;
extern QW D_002C1FA0;

/* a GLINT keeps a quadword where the RIP has its float at 0x20 */
struct GLINTWORDS {
    u8 unknown_0x0[0x20];
    QW field_0x20;
};

void InitGlint__FP5GLINTP6VECTORfP2SO(struct RIP *glint, QW pos, float fparg, struct SO *psoTouch) {
    InitRip__FP3RIPP6VECTORfP2SO(glint, pos, fparg, psoTouch);
    glint->dtLifetime = 0.5f;
    glint->field_0x30 = D_002C1F90;
    ((struct GLINTWORDS *)glint)->field_0x20 = D_002C1FA0;
}
