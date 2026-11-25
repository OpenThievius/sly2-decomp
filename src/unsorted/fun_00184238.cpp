#include "types.h"
// the object of a Splice member getter (the D_002D1EA8 table): its class is not known, only the float at 0x110 this one reads
struct MEMBEROWNER {
    u8 unknown_0x0[0x110];
    f32 offset;
};
extern "C" float D_002BF660;
void func_00184238(MEMBEROWNER *self, float *out)
{
    *out -= self->offset - (D_002BF660 - 150.0f);
}
