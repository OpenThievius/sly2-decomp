#include "cvector.h"
extern "C" {
void func_00116D28(void *);
void Vector_Clear(CVECTOR *self) {
    func_00116D28(&self->ary);
    VECTORLISTENER *node = self->plistener;
    if (node != 0) {
        do {
            node->OnClear();
            node = node->pnext;
        } while (node != 0);
    }
}
}
