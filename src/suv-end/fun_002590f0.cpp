// SPDX-License-Identifier: GPL-3.0-or-later
#include "emitter.h"
#include "alloc.h"
extern "C" {
EMITB *PvAllocSwCopyImpl__FiPv(ALLOCREQ *, EMITB *);
EMITB *func_002590F0(EMITTER *emitter, s32 ensk) {
    if (ensk == 1) {
        emitter->ensured = ensk;
        s32 *refcount = &emitter->pemitb->cref;
        s32 value = *refcount;
        if (value >= 2) {
            *refcount = value - 1;
            ALLOCREQ request;
            request.cb = 0x100;
            request.cbAlign = 0x10;
            EMITB *fresh = PvAllocSwCopyImpl__FiPv(&request, emitter->pemitb);
            emitter->pemitb = fresh;
            fresh->cref = ensk;
        }
    }
    return emitter->pemitb;
}
}
