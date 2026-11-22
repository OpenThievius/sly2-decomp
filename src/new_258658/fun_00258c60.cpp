// SPDX-License-Identifier: GPL-3.0-or-later
#include "emitter.h"
extern "C" {
EMITPARAMS *PemitripEnsureEmitter(EMITTER *, s32);
void SetEmitterRipt(EMITTER *, s32);
extern s32 B_002DE750;

s32 *func_00258C60(EMITTER *emitter, s32 ensk) {
    EMITPARAMS *params;
    s32 *result;

    if (ensk == 1) {
        SetEmitterRipt(emitter, 2);
        params = &emitter->pemitb->params;
    } else {
        params = PemitripEnsureEmitter(emitter, ensk);
    }
    if (params->kind == 2) {
        result = &params->payload;
    } else {
        result = &B_002DE750;
    }
    return result;
}
}
