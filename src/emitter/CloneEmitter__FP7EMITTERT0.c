/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "emitter.h"

void CloneXfm();

void CloneEmitter__FP7EMITTERT0(struct EMITTER *emitter) {
    struct EMITB *emitb;

    CloneXfm();
    emitb = emitter->pemitb;
    emitb->cref += 1;
}
