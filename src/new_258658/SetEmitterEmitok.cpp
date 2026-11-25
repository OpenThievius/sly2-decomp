// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct SZ { int size; int align; };
struct PEMITB { u8 unknown_0x0[0x10]; int emitok; u8 unknown_0x14[0x1C]; int p30; };
struct INNER { u8 unknown_0x0[0x10]; int value; };
struct OBJ { u8 unknown_0x0[0xE4]; INNER *inner; };
extern "C" void *PvAllocSwClearImpl__Fi(SZ *);
extern "C" PEMITB *PemitbEnsureEmitter(OBJ *, int);
static inline int Alloc(int size)
{
    SZ request;
    request.size = size;
    request.align = 0x10;
    return (sptr)PvAllocSwClearImpl__Fi(&request);
}
extern "C" void SetEmitterEmitok(OBJ *obj, int value)
{
    int current = obj->inner->value;
    if (current != value) {
        if (current == 0) {
            PEMITB *emitter = PemitbEnsureEmitter(obj, 1);
            emitter->emitok = value;
            switch (value) {
            case 1:
                emitter->p30 = Alloc(0x20);
                break;
            case 2:
                emitter->p30 = -1;
                break;
            case 3:
                emitter->p30 = Alloc(0x30);
                break;
            }
        }
    }
}
