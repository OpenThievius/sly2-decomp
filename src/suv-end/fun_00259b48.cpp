#include "lo.h"
extern "C" {
void func_00259B48(BASIC **arg0, BASIC *arg1) {
    if (arg1 != 0)
        arg1->OnAdd();
    BASIC *old = *arg0;
    if (old != 0)
        old->Slot2();
    *arg0 = arg1;
}
}
