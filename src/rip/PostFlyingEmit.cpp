// SPDX-License-Identifier: GPL-3.0-or-later
#include "rip.h"
extern "C" {
void func_001CE9B8(RIP *rip, EMITB *emitb);

/* a FLYING RIP keeps what its emitter gave it after the RIP */
struct FLYING : RIP {
    s32 field_0xF0; /* PostFlyingEmit: the emitter's info word at 0xC */
    s32 field_0xF4; /* PostFlyingEmit: the emitter's word at 0xF0 */
};

void PostFlyingEmit(FLYING *flying, EMITB *emitb) {
    func_001CE9B8(flying, emitb);
    flying->field_0xF0 = emitb->pinfo->field_0xC;
    flying->field_0xF4 = emitb->params.payload;
}

}
