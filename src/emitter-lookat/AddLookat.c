/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "lookat.h"

s32 FLookatInList(struct LOOKAT *plookat);
void InsertXfAct(struct ALO *palo, struct XF *pxf, struct LOOKAT *plookat);

void AddLookat(struct LOOKAT *plookat) {
    if (FLookatInList(plookat) == 0) {
        InsertXfAct(plookat->palo, plookat->pxf, plookat);
    }
}
