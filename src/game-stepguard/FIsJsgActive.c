/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jsg.h"

s32 FIsJsgActive(struct JSG *jsg) {
    return jsg->fRunning;
}
