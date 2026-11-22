// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "murray.h"
extern "C" int FInvulnerableJt(JT *, int);
extern "C" int func_00194640(void *, int);
int FInvulnerableMurray(MURRAY *pmurray, int grftak)
{
    switch (pmurray->state) {
    case 20:
        if (grftak == 0x4000)
            return 1;
        break;
    case 15:
        return 1;
    case 13:
        if (func_00194640(pmurray->PvAttach(), grftak) != 0)
            return 1;
        break;
    }
    return FInvulnerableJt(pmurray, grftak);
}
