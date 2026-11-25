// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
extern "C" void SetAmbGrf(AMB *amb, int grf, int arg);
extern "C" void SetAmbSilent(AMB *amb, int silent)
{
    if (silent == 0) {
        amb->Slot7();
        return;
    }
    int grf = 0x1FF;
    int result = amb->Slot8();
    if (result != 2)
        grf = 0x3FF;
    SetAmbGrf(amb, grf, 8);
}
