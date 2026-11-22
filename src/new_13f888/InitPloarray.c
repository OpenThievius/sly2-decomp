/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* a growable array of object pointers: AppendPloarray (cploMax, cplo, aplo) */
struct PLOARRAY {
    /* 0x0 */ void *field_0x0;      /* InitPloarray sets retail's 0x2CBE50 */
    /* 0x4 */ s32 cploMax;
    /* 0x8 */ s32 cplo;
    /* 0xC */ s32 *aplo;
};

extern char D_002CBE50[];

struct PLOARRAY *InitPloarray(struct PLOARRAY *pploarray) {
    pploarray->cploMax = 0;
    pploarray->field_0x0 = D_002CBE50;
    pploarray->cplo = 0;
    pploarray->aplo = 0;
    return pploarray;
}
