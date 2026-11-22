/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cplcy.h"

void UpdateCplcy(void);

void UpdateCplcy_thunk(void) {
    UpdateCplcy();
}
