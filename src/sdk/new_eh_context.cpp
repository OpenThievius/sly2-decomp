/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "ehcontext.h"
extern "C" {
void __terminate(void);
void *malloc(u32 size);
void *memset(void *destination, s32 value, u32 size);
EHCONTEXTBLOCK *new_eh_context(void) {
    EHCONTEXTBLOCK *block;
    block = (EHCONTEXTBLOCK *)malloc(0x18);
    if (block == 0) {
        __terminate();
    }
    memset(block, 0, 0x18);
    block->context.dynamicHandlerChain = block->handlerChain;
    return block;
}
}
