// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "emitter.h"
#include "alloc.h"
extern "C" void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
extern "C" EMITB *func_002590F0(EMITTER *, int);
static inline int Alloc(int size)
{
    ALLOCREQ request;
    request.cb = size;
    request.cbAlign = 0x10;
    return (sptr)PvAllocSwClearImpl__Fi(&request);
}
extern "C" void SetSuvSuvs(EMITTER *emitter, int value)
{
    int current = emitter->pemitb->emitok;
    if (current != value) {
        if (current == 0) {
            EMITB *emitb = func_002590F0(emitter, 1);
            emitb->emitok = value;
            switch (value) {
            case 1:
                emitb->field_0x30 = Alloc(0x20);
                break;
            case 2:
                emitb->field_0x30 = -1;
                break;
            case 3:
                emitb->field_0x30 = Alloc(0x30);
                break;
            }
        }
    }
}
