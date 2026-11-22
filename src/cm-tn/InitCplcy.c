/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

extern void *D_002CD570[18];

struct CPLCY *InitCplcy(struct CPLCY *policy) {
    policy->vtable = D_002CD570;
    return policy;
}
