// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
/* a hide part of the player: an object whose slot 21 (LO::Slot21) hides (0) or shows (1) it */
struct PART : LO {};
extern "C" void func_00205D10();
void SetSlyHide(SLY *pjt, int fHide)
{
    func_00205D10();
    if (fHide != 0) {
        pjt->apartHide[0]->Slot21(0);
        pjt->apartHide[1]->Slot21(0);
        pjt->apartHide[2]->Slot21(0);
    } else {
        pjt->apartHide[0]->Slot21(1);
        pjt->apartHide[1]->Slot21(1);
        pjt->apartHide[2]->Slot21(1);
    }
}
