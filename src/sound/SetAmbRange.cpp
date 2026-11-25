// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" void SetAmbRange(AMB *pamb, float lmMin, float lmMax)
{
if (lmMax <= lmMin) lmMax = lmMin + 1.0f; pamb->lmMin = lmMin; pamb->lmMax = lmMax;
}
