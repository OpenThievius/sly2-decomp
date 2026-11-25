#include "cvector.h"
extern "C" {
void Vector_NotifyAdd(CVECTOR *self, int arg1) {
    VECTORLISTENER *node = self->plistener;
    if (node != 0) {
        do {
            node->OnAdd(arg1);
            node = node->pnext;
        } while (node != 0);
    }
}
}
