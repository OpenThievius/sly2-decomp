/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void *InitCplcy(void *);                            /* extern */
extern void *D_002DB858[18];                        /* the policy's vtable */

struct CPTN *InitCptn(struct CPTN *cptn) {
    InitCplcy(cptn);
    cptn->vtable = D_002DB858;
    return cptn;
}
