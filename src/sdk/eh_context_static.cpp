/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "ehcontext.h"
extern "C" {
void *memset(void *, int, unsigned);
extern EHCONTEXT B_00450258;
extern s32 B_00450268; /* set once the context is built */
extern u8 B_00450270;  /* where the context's handler chain starts */
EHCONTEXT *eh_context_static(void) {
    if (B_00450268 == 0) {
        B_00450268 = 1;
        memset(&B_00450258, 0, 0x10);
        B_00450258.dynamicHandlerChain = &B_00450270;
    }
    return &B_00450258;
}
}
