#include "types.h"
struct Elem { u8 unknown_0x0[0x18]; u64 mask; };
struct Kind { u8 unknown_0x0[0x20]; u64 mask; };
struct Table { u8 unknown_0x0[8]; void *shape; Kind **kinds; Elem **elems; };
extern "C" int func_001EA688(void *);
extern "C" u64 func_001EA6C8(Table *table, int row, int column)
{
    u64 mask = table->kinds[row]->mask;
    Elem *elem = table->elems[row * func_001EA688(table->shape) + column];
    if (elem) mask |= elem->mask;
    return mask;
}
