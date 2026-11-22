// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "murray.h"
struct XPSIDE { u8 unknown_0x0[0xC]; SO *pso; u8 unknown_0x10[0x30]; };
struct XP { XPSIDE side[2]; VECTOR normal; };
/* The word of the player at 0x1908 that this function sets (murray.h has it inside an unknown span). */
struct MURRAYXPVIEW {
    u8 unknown_0x0[0x1908];
    s32 field_0x1908;
};
extern "C" {
extern float D_002C0A38;
extern float D_002C3C60[];
extern char B_003DD490[];
void AdjustStepNewXp(void *, void *, int);
void AdjustJtZapNewXp(void *, void *, int);
void func_0019E9C8(void *, void *, int);
void *CloneMqList(void *, void *);
void PrependMqList(void *, void *, void *);
QW GCosAngle(QW, QW);
}

extern "C" void AdjustMurrayNewXp(MURRAY *m, XP *pxp, int iside)
{
    AdjustStepNewXp(m, pxp, iside);
    switch (m->state) {
    case 0xE:
        AdjustJtZapNewXp((char *)m + 0xDF0, pxp, iside);
        break;
    case 0xC: {
        int charges = m->field_0x1840;
        if (charges != 1) break;
        SO *pother = pxp->side[1 - iside].pso;
        if (pother->FIsLocked() != 0) {
            float v = pxp->normal.z;
            if (v < 0.7f) {
                QW velocity = m->GetVelocityVec();
                QW cosine = GCosAngle(velocity, *(QW *)&pxp->normal);
                int hit = LaneX(cosine) < D_002C0A38;
                if (hit)
                    ((MURRAYXPVIEW *)m)->field_0x1908 = charges;
            }
        }
        break;
    }
    case 3:
        if (m->field_0x13D8 == 1) {
            if (0.7f < D_002C3C60[iside] * pxp->normal.z) {
                void *pmq = CloneMqList(B_003DD490, pxp);
                PrependMqList(B_003DD490, pmq, &m->field_0x13E4);
            }
        }
        break;
    case 0x14:
        func_0019E9C8(m->PvPipe(), pxp, iside);
        break;
    }
}
