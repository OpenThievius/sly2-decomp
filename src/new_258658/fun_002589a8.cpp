// SPDX-License-Identifier: GPL-3.0-or-later
#include "emitter.h"
extern "C" {

EMITPARAMS *PemitblipEnsureEmitter(EMITTER *, s32);
EMITPARAMS *PemitripEnsureEmitter(EMITTER *, s32);

void func_002589A8(EMITTER *emitter, s32 kind) {
    switch (kind) {
    case 0:
        PemitblipEnsureEmitter(emitter, 1);
        return;
    case 1:
        PemitripEnsureEmitter(emitter, 1);
        break;
    }
}
}
