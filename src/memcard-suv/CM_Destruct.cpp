// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"
/* The camera manager's own fields, read by its destructor: four owned objects, released through BASIC's slot 2 (cm.h's CM keeps
   its policies at 0x450, which these lie inside, so this stays a local view of it). */
struct CM {
    u8 unknown_0x0[0x484];
    /* 0x484 */ BASIC *pbasic484;
    /* 0x488 */ BASIC *pbasic488;
    u8 unknown_0x48C[0x5E0 - 0x48C];
    /* 0x5E0 */ BASIC *pbasic5E0;
    /* 0x5E4 */ BASIC *pbasic5E4;
};
extern "C" void BASIC_Destruct(void *, int);
static inline void Release(BASIC *pbasic)
{
    if (pbasic != 0) {
        pbasic->Slot2();
    }
}
void CM_Destruct(CM *cm, int flags)
{
    Release(cm->pbasic5E4);
    Release(cm->pbasic5E0);
    Release(cm->pbasic488);
    Release(cm->pbasic484);
    BASIC_Destruct(cm, flags);
}
