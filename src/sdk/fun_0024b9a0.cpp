/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
extern "C" {
void func_00254988(IPUSTATE *state);
s32 func_0024B9A0(MPEGHANDLE *handle) {
    func_00254988(&handle->state->ipuState);
    return 1;
}
}
