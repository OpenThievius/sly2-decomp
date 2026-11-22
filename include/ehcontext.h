/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The exception-handling context of a thread (0x10 bytes): the dynamic handler chain at 4 (__get_dynamic_handler_chain returns
   its address) and the exception info at 8 (__get_eh_info). eh_context_static builds the program's one static context at
   0x450258 (its chain starts at 0x450270); new_eh_context allocates an EHCONTEXTBLOCK, the context followed by the 8 bytes its
   chain starts in. Names are ours. C and C++. */
#ifndef SLY2_EHCONTEXT_H
#define SLY2_EHCONTEXT_H
#include "types.h"
typedef struct EHCONTEXT {
    s32 field_0x0;
    void *dynamicHandlerChain; /* 0x04 */
    u8 info[8];                /* 0x08 */
} EHCONTEXT;

typedef struct EHCONTEXTBLOCK {
    EHCONTEXT context;
    u8 handlerChain[8];        /* 0x10 */
} EHCONTEXTBLOCK;

#if defined(__mips__)
typedef char check_EHCONTEXT_size[(sizeof(EHCONTEXT) == 0x10) ? 1 : -1];
typedef char check_EHCONTEXTBLOCK_size[(sizeof(EHCONTEXTBLOCK) == 0x18) ? 1 : -1];
#endif
#endif
