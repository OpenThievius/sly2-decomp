/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void *InitCplcy(void *);
extern char D_002CD450[];

struct CPLCY *func_00151208(struct CPLCY *policy) {
    InitCplcy(policy);
    policy->vtable = D_002CD450;
    return policy;
}
