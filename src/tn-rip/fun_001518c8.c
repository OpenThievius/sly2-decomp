/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void *InitCplcy(void *);
extern char D_002CD3C0[];

struct CPLCY *func_001518C8(struct CPLCY *policy) {
    InitCplcy(policy);
    policy->vtable = D_002CD3C0;
    return policy;
}
