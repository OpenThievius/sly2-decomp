/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mpeg.h"
extern "C" {
s32 sceMpegIsEnd(MPEGHANDLE *handle) {
    return handle->state->done;
}
}
