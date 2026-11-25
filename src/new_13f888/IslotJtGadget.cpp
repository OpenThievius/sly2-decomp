#include "jt.h"
int IslotJtGadget(JT *self, int id)
{
    for (int index = 0; index < 3; index++) {
        if (id == self->aslot[index].gadget) return index;
    }
    return -1;
}
