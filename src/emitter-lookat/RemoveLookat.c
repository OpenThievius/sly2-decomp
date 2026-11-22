/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "lookat.h"

s32 FLookatInList(struct LOOKAT *plookat);
void RemoveXfAct(struct ALO *palo, struct XF *pxf, struct LOOKAT *plookat);

void RemoveLookat(struct LOOKAT *plookat) {
    if (FLookatInList(plookat) != 0) {
        RemoveXfAct(plookat->palo, plookat->pxf, plookat);
    }
}
