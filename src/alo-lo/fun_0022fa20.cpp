// SPDX-License-Identifier: GPL-3.0-or-later
#include "alo.h"
#include "sw.h"
#include "xf.h"

extern "C" {
void AddAloToRenderTree(ALO *);
void ReinsertSwRoot(SW *, s32);
void RemoveAloFromRenderTree(ALO *);
extern SW B_003DD490;

void func_0022FA20(ALO *palo)
{
    if ((int)(palo->grfo >> 0x3C) & 1) {
        s32 generation = palo->field_0x140;
        if ((generation != -1) && (palo->pxfRoot->generation != generation)) {
            RemoveAloFromRenderTree(palo);
            AddAloToRenderTree(palo);
        }
        if (palo->psoParent == 0) {
            ReinsertSwRoot(&B_003DD490, palo->proot);
        }
    }
}
}
