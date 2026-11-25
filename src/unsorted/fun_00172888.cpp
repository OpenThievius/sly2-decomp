#include "sly2.h"
struct OBJ { u8 unknown_0x0[0x10]; f32 key; };
int func_00172888(OBJ *a, OBJ *b)
{
    return a->key < b->key;
}
