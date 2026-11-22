/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void CPLCY_Destruct(void);

void CPLCY_Destruct_thunk(void) {
    CPLCY_Destruct();
}
