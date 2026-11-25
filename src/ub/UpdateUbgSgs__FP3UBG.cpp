// 0x1A1F68 UpdateUbgSgs__FP3UBG
#include "types.h"

// the class behind the symbol's UBG: only the pointer at 0x10 this function reads, to an int it tests against zero
struct UBG {
    u8 unknown_0x0[0x10];
    s32 *pcount;
};

extern "C" void func_801A0B40(void *p, int state);

void UpdateUbgSgs__FP3UBG(UBG *p)
{
    if (*p->pcount > 0) {
        func_801A0B40(p, 0);
    } else {
        func_801A0B40(p, 8);
    }
}
