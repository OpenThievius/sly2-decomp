// SPDX-License-Identifier: GPL-3.0-or-later
#include "cplcy.h"
/* The camera manager's destructor releases four objects its policies own, each through BASIC's slot 2: the look policy's two
   reference pointers (CPLOOK, cplcy.h) and K30CAM's two. Both sit past the CPLCY header cm.h gives their members, so the
   destructor reads CM as this view (the same offsets as cm.h's cplook and k30cam). */
struct CMVIEW {
    u8 unknown_0x0[0x450];
    CPLOOK cplook;
    u8 unknown_0x48C[0x520 - 0x48C];
    K30CAM k30cam;
};
extern "C" void BASIC_Destruct(void *, int);
static inline void Release(void *pbasic)
{
    if (pbasic != 0) {
        ((BASIC *)pbasic)->Slot2();
    }
}
void CM_Destruct(CM *cm, int flags)
{
    CMVIEW *pview = (CMVIEW *)cm;
    Release(pview->k30cam.field_0xC4);
    Release(pview->k30cam.field_0xC0);
    Release(pview->cplook.field_0x38);
    Release(pview->cplook.ambience);
    BASIC_Destruct(cm, flags);
}
