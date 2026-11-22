/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SCRIPT, a script object, and its commands. A SCRIPT is an LO (0x50 bytes; InitScript calls InitLo, PostLoadScript PostLoLoad)
   that keeps its commands in a singly linked list at 0x50 (InitScript: InitSl with the link at 0x18; PcmdAllocScript appends).
   A command is a 0x20-byte entry of a slot heap (B_003E1548): type at 0x0, the object id at 0x4, the arguments from 0x8,
   the link at 0x18. The arguments depend on the type: PcmdAllocScript's callers AddScriptRun (6), AddScriptGoto (7),
   func_00170B60 (1) and func_00170BA0 (2) each fill their own. C and C++. */
#ifndef SLY2_SCRIPT_H
#define SLY2_SCRIPT_H
#include "types.h"
#include "sl.h"
#include "bytes8.h"

struct SCRIPT {
    u8 unknown_0x0[0x50];
    SL slPcmd; /* InitScript (InitSl, link 0x18), PcmdAllocScript (AppendSlEntry) */
};

struct PCMD {
    s32 type;  /* PcmdAllocScript stores its second argument */
    s32 oid;   /* PcmdAllocScript stores its third argument */
};

struct PCMDRUN { /* type 6 */
    struct PCMD pcmd;
    s32 field_0x8; /* AddScriptRun's third argument */
    s32 field_0xC; /* AddScriptRun's fourth argument */
};

struct PCMDGOTO { /* type 7 */
    struct PCMD pcmd;
    u8 unknown_0x8[0x8];
    s32 field_0x10; /* AddScriptGoto's fourth argument */
    f32 field_0x14; /* AddScriptGoto's float argument */
};

struct PCMDPAYLOAD { /* types 1 and 2 */
    struct PCMD pcmd;
    struct BYTES8 payload; /* func_00170B60 and func_00170BA0 copy 8 bytes here */
};
#endif
