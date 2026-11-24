#include "mpeg.h"
int func_00252148(MPEGDEC *, int);
void func_002542B8(MPEGDEC *);
void func_00253C80(MPEGDEC *self) {
    self->field_0xFC = 0;
    self->newGop = 1;
    self->gopBase = self->maxPictureIndex + 1;
    func_00252148(self, 1);
    func_00252148(self, 5);
    func_00252148(self, 6);
    func_00252148(self, 1);
    func_00252148(self, 6);
    func_00252148(self, 6);
    self->field_0x1B4 = func_00252148(self, 1);
    self->field_0x1B8 = func_00252148(self, 1);
    func_002542B8(self);
}
