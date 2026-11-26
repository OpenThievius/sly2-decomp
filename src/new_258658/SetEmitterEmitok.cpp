// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "emitter.h"
struct SZ { int size; int align; };
extern "C" void *PvAllocSwClearImpl__Fi(SZ *);
extern "C" EMITB *PemitbEnsureEmitter(EMITTER *, int);
static inline int Alloc(int size)
{
    SZ request;
    request.size = size;
    request.align = 0x10;
    return (sptr)PvAllocSwClearImpl__Fi(&request);
}
extern "C" void SetEmitterEmitok(EMITTER *emitter, int value)
{
    int current = emitter->pemitb->emitok;
    if (current != value) {
        if (current == 0) {
            EMITB *block = PemitbEnsureEmitter(emitter, 1);
            block->emitok = value;
            switch (value) {
            case 1:
                block->field_0x30 = Alloc(0x20);
                break;
            case 2:
                block->field_0x30 = -1;
                break;
            case 3:
                block->field_0x30 = Alloc(0x30);
                break;
            }
        }
    }
}
