// SPDX-License-Identifier: GPL-3.0-or-later
#include "emitter.h"
extern "C" {
EMITPARAMS *PemitblipEnsureEmitter(EMITTER *, s32);
void SetEmitterBlipmk(EMITTER *, s32);
extern s32 B_002DE750;

s32 *func_00258EC8(EMITTER *emitter, s32 ensk) {
    EMITPARAMS *params;
    s32 *result;

    if (ensk == 1) {
        SetEmitterBlipmk(emitter, 1);
        params = &emitter->pemitb->params;
    } else {
        params = PemitblipEnsureEmitter(emitter, ensk);
    }
    if (params->kind == 1) {
        result = &params->payload;
    } else {
        result = &B_002DE750;
    }
    return result;
}
}
