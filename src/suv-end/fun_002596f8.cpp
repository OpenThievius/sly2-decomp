// SPDX-License-Identifier: GPL-3.0-or-later
#include "emitter.h"
extern "C" {
EMITPARAMS *func_002593B8(EMITTER *, s32);
void func_00259608(EMITTER *, s32);
extern s32 B_002DE750;

s32 *func_002596F8(EMITTER *emitter, s32 ensk) {
    EMITPARAMS *params;
    s32 *result;

    if (ensk == 1) {
        func_00259608(emitter, 2);
        params = &emitter->pemitb->params;
    } else {
        params = func_002593B8(emitter, ensk);
    }
    if (params->kind == 2) {
        result = &params->payload;
    } else {
        result = &B_002DE750;
    }
    return result;
}
}
