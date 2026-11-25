// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" void SetAmbGrf(AMB *, unsigned short, unsigned short);

extern "C" void PauseAmb(AMB *pamb)
{
    pamb->cPause++;
    if (pamb->cPause == 1) SetAmbGrf(pamb, 6, 2);
}
