#include "shd.h"
#include "types.h"
struct Elem { u8 unknown_0x0[0x18]; u64 mask; };
struct Kind { u8 unknown_0x0[0x20]; u64 mask; };
extern "C" int func_001EA688(void *);
/* a TEX (shd.h): owner is its shader, abmp its bitmap records (here as pointers, each with a mask), apal the palette records */
extern "C" u64 func_001EA6C8(TEX *table, int row, int column)
{
    u64 mask = ((Kind **)table->abmp)[row]->mask;
    Elem *elem = ((Elem **)table->apal)[row * func_001EA688(table->owner) + column];
    if (elem) mask |= elem->mask;
    return mask;
}
