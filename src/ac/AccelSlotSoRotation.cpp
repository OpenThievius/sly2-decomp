// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
#include "sly2.h"
void AccelSoTowardMatSmooth(SO *, float, MATRIX3 *, SMP *);
void AccelSlotSoRotation(SLOTSO *self, float deltaTime)
{
    AccelSoTowardMatSmooth(self, deltaTime, (MATRIX3 *)&self->rotation, &self->smp);
}
