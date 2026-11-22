// SPDX-License-Identifier: GPL-3.0-or-later
#include "emitter.h"
extern "C" {
EMITPARAMS *func_00259330(EMITTER *, s32);
void func_00259830(EMITTER *, s32);
extern s32 B_002DE750;

s32 *func_00259960(EMITTER *emitter, s32 ensk) {
    EMITPARAMS *params;
    s32 *result;

    if (ensk == 1) {
        func_00259830(emitter, 1);
        params = &emitter->pemitb->params;
    } else {
        params = func_00259330(emitter, ensk);
    }
    if (params->kind == 1) {
        result = &params->payload;
    } else {
        result = &B_002DE750;
    }
    return result;
}
}
