#include "types.h"
extern "C" {
/* a counted object that VirtualRefPtr_Assign takes and drops a reference of through its vtable at 0xC (slot 1: take, slot 2: drop) */
struct COUNTEDOBJ {
    u8 unknown_0x0[0xC];
    virtual void TakeRef();
    virtual void DropRef();
};
void VirtualRefPtr_Assign(COUNTEDOBJ **arg0, COUNTEDOBJ *arg1) {
    if (arg1 != 0)
        arg1->TakeRef();
    COUNTEDOBJ *old = *arg0;
    if (old != 0)
        old->DropRef();
    *arg0 = arg1;
}
}
