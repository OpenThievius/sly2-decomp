// SPDX-License-Identifier: GPL-3.0-or-later
#include "emitter.h"
extern "C" void SetEmitterEmitok(EMITTER *, int);
int func_00258B00(EMITTER *emitter, int ensk)
{
    if (ensk == 1)
        SetEmitterEmitok(emitter, 1);
    return emitter->pemitb->field_0x30;
}
