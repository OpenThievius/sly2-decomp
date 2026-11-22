/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "lookat.h"

void InvalidateXfSegment(struct ALO *palo, struct XF *pxf);
void SetXfKind(struct ALO *palo, struct XF *pxf, s32 xfkind);

void ActivateAct(struct LOOKAT *plookat) {
    SetXfKind(plookat->palo, plookat->pxf, plookat->xfkind);
    InvalidateXfSegment(plookat->palo, plookat->pxf);
}
