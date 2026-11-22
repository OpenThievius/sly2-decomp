/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rip.h"

void AddRipRef__FP3RIP(struct RIP *rip) {
    rip->cref += 1;
}
