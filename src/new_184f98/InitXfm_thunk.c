/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct XFM;

void InitXfm(struct XFM *pxfm);                     /* extern */

void InitXfm_thunk(struct XFM *pxfm) {
    InitXfm(pxfm);
}
