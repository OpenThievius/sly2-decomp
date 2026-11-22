/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The SDK pad library's tables (0x2319E8 range): the per-slot table at 0x4505D0 (ports of four slots, 0x1C bytes a slot, 0x70 a
   port: the stride func_00243270 uses), the RPC client at 0x450580 and the request buffer at 0x4507C0 (0x80 bytes) the server
   answers in place. Names are ours, from what the readers do: func_00243270, func_00243388, func_00243458, scePadRead,
   scePadGetState, scePadSetActDirect (the slot table and its frames); scePadSetActAlign, scePadSetMainMode (the request).
   C and C++. */
#ifndef SLY2_PAD_H
#define SLY2_PAD_H
#include "types.h"

/* One half (0x80 bytes) of a slot's transfer buffer; the library keeps two and func_00243270 returns the one whose counter is
   not behind (the half the server wrote last). */
typedef struct PADFRAME {
    u8 unknown_0x0[0x58];
    s32 counter;      /* 0x58, func_00243270 compares the two halves' */
    u8 unknown_0x5C[0x4];
    s32 length;       /* 0x60, the number of bytes scePadRead copies out */
    u8 unknown_0x64[0xC];
    u8 state;         /* 0x70, func_00243388 returns it (0x63 stands for a closed slot) */
    u8 requestState;  /* 0x71, func_00243458 sets it (2 once a request RPC succeeds); func_00243388 reports 5 while state is 6 and
                         this is 2; scePadGetState returns it */
    u8 field_0x72;    /* scePadSetActDirect requires 1 */
    u8 unknown_0x73[0xD];
} PADFRAME;

/* The actuator command block scePadSetActDirect fills in. */
typedef struct PADACT {
    u8 unknown_0x0[0x4];
    s32 pending;      /* 0x04, set to 1 */
    s32 length;       /* 0x08, set to 6 */
    u8 data[8];       /* 0x0C */
} PADACT;

typedef struct PADSLOT {
    PADFRAME *frames; /* 0x00, the two halves */
    PADACT *act;      /* 0x04 */
    u8 unknown_0x8[0x8];
    s32 opened;       /* 0x10, every reader returns early when 0 */
    u8 unknown_0x14[0x8];
} PADSLOT;

typedef struct PADPORT {
    PADSLOT slot[4];
} PADPORT;

/* The RPC client the requests go through. */
typedef struct PADCLIENT {
    u8 unknown_0x0[0x24];
    s32 serverReady;  /* 0x24 */
} PADCLIENT;

/* The request buffer: a command, its port and slot, two command-specific words, the server's answer at 0x14. */
typedef struct PADREQUEST {
    s32 command;
    s32 port;
    s32 slot;
    union {
        u8 bytes[8];  /* scePadSetActAlign, command 8: six bytes of alignment data */
        struct {
            s32 argument0;
            s32 argument1;
        } main;       /* scePadSetMainMode, command 6 */
    } arguments;
    s32 result;       /* 0x14 */
} PADREQUEST;

#if defined(__mips__)
typedef char check_PADFRAME_size[(sizeof(PADFRAME) == 0x80) ? 1 : -1];
typedef char check_PADFRAME_state[((uptr)&((PADFRAME *)0)->state == 0x70) ? 1 : -1];
typedef char check_PADSLOT_size[(sizeof(PADSLOT) == 0x1C) ? 1 : -1];
typedef char check_PADPORT_size[(sizeof(PADPORT) == 0x70) ? 1 : -1];
typedef char check_PADREQUEST_result[((uptr)&((PADREQUEST *)0)->result == 0x14) ? 1 : -1];
#endif
#endif
