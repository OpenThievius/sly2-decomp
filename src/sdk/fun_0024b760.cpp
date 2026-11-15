// SPDX-License-Identifier: GPL-3.0-or-later
#include "mpeg.h"
extern "C" {
void func_0024B148(MPEGHANDLE *handle, int first, int second);
void func_0024B2B8(MPEGHANDLE *handle, int first, int second);
void func_0024B760(MPEGHANDLE *handle, int first, int second) {
    if (handle->state->pictureStructure != 3) {
        func_0024B2B8(handle, first, second);
    } else {
        func_0024B148(handle, first, second);
    }
}
}
