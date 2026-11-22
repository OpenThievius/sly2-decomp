// SPDX-License-Identifier: GPL-3.0-or-later
#include "attach.h"
#include "stepguard.h"
#include "vu0inline.h"
#include "ps2inline.h"

struct CSF { char unknown_0x0; };
struct CSFSLOT { char unknown_0x0; CSF frame; char unknown_0x2[2]; int count; int list; };
extern "C" {
SENSORENTRY *PentryFindSensorLo(SENSOR *psensor, LO *plo);
QW PosLoWorld(LO *plo);
void SetSensorEntryState(SENSOR *psensor, SENSORENTRY *pentry, int state);
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void bevy_camera_follow_push_out(SW *psw, QW, QW, void *pfnFilter, STEPGUARD *pguard, int *pcount, int *plist);
int PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(int, QW, QW, int, int, int);
extern SW B_003DD490; /* the world */
extern char FFilterSensorSight[];
extern float g_2bf638;
extern DL B_003E1444; /* the world list of guards */
}

extern "C" void ForgetJtGuards(ATTACH *pattach)
{
    CSFSLOT slot;
    QW posGuard;
    QW posTarget;
    for (STEPGUARD *pguard = (STEPGUARD *)B_003E1444.head; pguard != 0; pguard = pguard->pnext) {
        SENSORENTRY *pentry = PentryFindSensorLo(pguard->psensor, pattach->pjt);
        if (pentry != 0 && pentry->state != 0 && (*(int *)((char *)pguard->psensor + 0xF8) & 1) == 0) {
            posGuard = PosLoWorld(pguard);
            posTarget = PosLoWorld(pattach->pjt);
            float distance = LaneX(SqrtX(SquaredLength(VectorSub(posGuard, posTarget))));
            int fOutOfRange = g_2bf638 < distance;
            if (fOutOfRange) {
                SetSensorEntryState(pguard->psensor, pentry, 0);
            } else {
                CStackFrame_Construct(&slot.frame);
                bevy_camera_follow_push_out(&B_003DD490, posGuard, posTarget, FFilterSensorSight, pguard, &slot.count, &slot.list);
                if (PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG(0, posGuard, posTarget, slot.count, slot.list, 0) == 0) {
                    CStackFrame_Destructor(&slot.frame, 2);
                } else {
                    SetSensorEntryState(pguard->psensor, pentry, 0);
                    CStackFrame_Destructor(&slot.frame, 2);
                }
            }
        }
    }
}
