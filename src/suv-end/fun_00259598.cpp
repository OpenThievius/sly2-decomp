// SPDX-License-Identifier: GPL-3.0-or-later
#include "emitter.h"
extern "C" void SetSuvSuvs(EMITTER *, int);
int func_00259598(EMITTER *emitter, int ensk)
{
    if (ensk == 1)
        SetSuvSuvs(emitter, 1);
    return emitter->pemitb->field_0x30;
}
