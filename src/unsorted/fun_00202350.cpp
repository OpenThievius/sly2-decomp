#include "types.h"
struct OBJ { u8 unknown_0x0[0x10]; u64 flags; u8 unknown_0x18[0x70 - 0x18]; s32 count; };
extern "C" int func_00202350(void *unused, OBJ *obj)
{
    int result = 0;
    if (!(obj->flags & 0x1000000000000UL)) result = obj->count > 0;
    return result;
}
