// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"
#include "clock.h"
struct SENSOREVENT { SENSORENTRY *pentry; s32 *pstate; s32 *pstateNew; };
extern "C" {
extern char B_002DEB30;
int FIsBasicDerivedFrom(void *, int);
void bevy_camera_follow_activity(char *, int, void *);
void SetSensorEntryState(SENSOR *psensor, SENSORENTRY *pentry, int nState)
{
    if (pentry == 0 || nState == pentry->state)
        return;
    if (pentry->state == 0)
        pentry->tFirst = g_2dded0.t;
    SENSOREVENT event;
    event.pentry = pentry;
    event.pstate = &pentry->state;
    event.pstateNew = &nState;
    psensor->HandleSpliceEvent(0x1C, 0, 3, (sptr)&event, 0);
    pentry->state = nState;
    pentry->tState = g_2dded0.t;
    if (nState == 1) {
        SO *psoParent = psensor->psoParent;
        if (psoParent != 0 && FIsBasicDerivedFrom(psoParent, 0x33) != 0)
            bevy_camera_follow_activity(&B_002DEB30, 0x13, psoParent);
    }
}
}
