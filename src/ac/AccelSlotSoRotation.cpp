// SPDX-License-Identifier: GPL-3.0-or-later
#include "slotso.h"
#include "sly2.h"
struct SMP;
void AccelSoTowardMatSmooth(SO *, float, MATRIX3 *, SMP *);
void AccelSlotSoRotation(SLOTSO *self, float deltaTime)
{
    AccelSoTowardMatSmooth(self, deltaTime, (MATRIX3 *)((char *)self + 0x1E0), (SMP *)((char *)self + 0x210));
}
