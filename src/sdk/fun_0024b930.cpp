/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "mpeg.h"
extern "C" {
void func_0024FA38(MPEGDEC *, const char *);
s32 func_0024B930(MPEGDEC *decoder, MPEGWORKAREA *area, s32 size, u32 alignment) {
    s32 start;
    u32 end;
    start = ((area->used + alignment - 1) / alignment) * alignment;
    end = start + size;
    if (area->base + area->size < end) {
        func_0024FA38(decoder, "work area size is too small");
        return 0;
    }
    area->used = end;
    return start;
}
}
