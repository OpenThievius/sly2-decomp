/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void *InitCplcy(void *);
extern char D_002CD408[];

struct CPLCY *func_00151610(struct CPLCY *policy) {
    InitCplcy(policy);
    policy->vtable = D_002CD408;
    return policy;
}
