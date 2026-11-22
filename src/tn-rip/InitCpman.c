/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void *InitCplcy(void *);
extern char D_002CD528[];

struct CPLCY *InitCpman(struct CPLCY *policy) {
    InitCplcy(policy);
    policy->vtable = D_002CD528;
    return policy;
}
