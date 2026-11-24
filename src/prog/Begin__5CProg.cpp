#include "types.h"
struct CPROG {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s8 byte10;
    u8 unknown_0x11[0x3F];
    s32 field50;
};
void Begin__5CProg(CPROG *prog)
{
    prog->field0 = 0;
    prog->field50 = 0;
    prog->fieldC = 0;
    prog->field8 = 0;
    prog->field4 = 0;
    prog->byte10 = 0;
}
