/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GUARDSCRIPTBEH, a guard's script behaviour (a GOAL: vtable at 0xC): it runs a SCRIPT's commands for a guard. SetGuardScript
   (it sets the script, the current command and the resume state), InitGuardScriptBeh, ExitGuardScriptBeh and FGuardScriptDone read
   the same offsets. C and C++ (SetGuardScript keeps its own C++ view with the virtuals). */
#ifndef SLY2_GUARDSCRIPTBEH_H
#define SLY2_GUARDSCRIPTBEH_H
#include "script.h"

struct STEPGUARD;

struct GUARDSCRIPTBEH {
    u8 unknown_0x0[0x10];
    struct STEPGUARD *pguard; /* the guard: ExitGuardScriptBeh removes sgs 0x21 from it, InitGuardScriptBeh adds it */
    u8 unknown_0x14[0x1C];
    struct SCRIPT *pscript;   /* SetGuardScript (0x30) */
    s32 context;              /* SetGuardScript */
    struct PCMD *pcmd;        /* the current command, 0 when done: SetGuardScript, FGuardScriptDone */
};
#endif
