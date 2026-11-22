/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "acrc.h"

struct CBinaryInputStream;

void CBinaryInputStream_Read_thunk(struct CBinaryInputStream *pbis, int size, void *destination); /* extern */

void LoadAcrcFromBrx(struct ACRC *pacrc, struct CBinaryInputStream *pbis) {
    CBinaryInputStream_Read_thunk(pbis, 0xC, pacrc->pos);
}
