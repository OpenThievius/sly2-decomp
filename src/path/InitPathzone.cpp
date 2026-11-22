// SPDX-License-Identifier: GPL-3.0-or-later
#include "pathzone.h"

extern "C" {
void InitDl__FP2DLi(DL *pdl, int ibDle);
void InitXfm(void *pxfm);

void InitPathzone(PATHZONE *ppathzone) {
    InitXfm(ppathzone);
    ppathzone->field_0x110 = -1;
    InitDl__FP2DLi(&ppathzone->dlItem, 0x60);
    ppathzone->ipathzone = -1;
}
}
