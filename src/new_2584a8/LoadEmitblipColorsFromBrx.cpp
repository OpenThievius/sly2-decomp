#include "sly2.h"
struct Bis;
#include "alloc.h"
#include "emitter.h"
struct B4 { char b[4]; };
extern "C" {
unsigned U16Read__18CBinaryInputStream(Bis *);
unsigned U8Read__18CBinaryInputStream(Bis *);
unsigned U32Read__18CBinaryInputStream(Bis *);
void *PvAllocSwImpl__Fi(ALLOCREQ *);
void FilterColorRgba8_1ed278(void *);
void LoadEmitblipColorsFromBrx(EMITTER *emitter, Bis *bis)
{
    int count = U16Read__18CBinaryInputStream(bis);
    if (count) {
        EMITPARAMS *blip = &emitter->pemitb->params;
        union { ALLOCREQ req; unsigned rgba; B4 raw; } u;
        u.req.cb = count * 4 + 4;
        u.req.cbAlign = 0x10;
        int *table = (int *)PvAllocSwImpl__Fi(&u.req);
        blip->table = table;
        blip->colorRanges = U8Read__18CBinaryInputStream(bis);
        int limit = 0x20;
        if (count <= 0x1f) limit = count;
        *table = limit;
        for (int index = 0; index < count; index++) {
            u.rgba = U32Read__18CBinaryInputStream(bis);
            FilterColorRgba8_1ed278(&u.rgba);
            if (index < *table) ((B4 *)(table + 1))[index] = u.raw;
        }
    }
}
}
