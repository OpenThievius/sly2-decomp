#include "types.h"
struct KIND { int type; };
struct TARGET { u8 unknown_0x0[0x18]; s32 value; u8 unknown_0x1C[0x14]; KIND *kind; };
struct JSG { u8 unknown_0x0[0x68]; TARGET *target; };
extern "C" int func_001E0128(JSG *jsg)
{
    TARGET *target = jsg->target;
    if (target == 0) return 0;
    if (target->kind->type == 9) return target->value;
    return 0;
}
