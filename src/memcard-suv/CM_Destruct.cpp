// SPDX-License-Identifier: GPL-3.0-or-later
#include "cplcy.h"
/* The camera manager's destructor releases four objects its policies own, each through BASIC's slot 2: the look policy's two
   reference pointers (CPLOOK, cplcy.h) and K30CAM's two. */
extern "C" void BASIC_Destruct(void *, int);
static inline void Release(void *pbasic)
{
    if (pbasic != 0) {
        ((BASIC *)pbasic)->Slot2();
    }
}
void CM_Destruct(CM *cm, int flags)
{
    Release(cm->k30cam.field_0xC4);
    Release(cm->k30cam.field_0xC0);
    Release(cm->cplook.field_0x38);
    Release(cm->cplook.ambience);
    BASIC_Destruct(cm, flags);
}
