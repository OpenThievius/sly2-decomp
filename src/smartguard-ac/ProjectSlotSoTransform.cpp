// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
#include "xf.h"
extern "C" {
void ProjectSoTransform(SO *pso);

void ProjectSlotSoTransform(SLOTSO *pso) {
    if (pso->state < 4) {
        if (pso->state >= 2) {
            XF *pxfLinear = pso->pxfLinear;
            s32 *accelLinear = pxfLinear->accel;
            accelLinear[2] = 0;
            accelLinear[1] = 0;
            pxfLinear->accel[0] = 0;
            XF *pxfAngular = pso->pxfAngular;
            s32 *accelAngular = pxfAngular->accel;
            accelAngular[2] = 0;
            accelAngular[1] = 0;
            pxfAngular->accel[0] = 0;
            pso->Slot70();
        }
    }
    ProjectSoTransform(pso);
}

}
