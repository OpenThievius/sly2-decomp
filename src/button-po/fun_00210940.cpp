#include "types.h"
struct Owner { u8 unknown_0x0[0x4638]; void *swObject; };
extern "C" void *PloFindSwObject_thunk(Owner *, int, int, int);
void func_00210940(Owner *owner)
{
    owner->swObject = PloFindSwObject_thunk(owner, 5, 0x620, 0);
}
