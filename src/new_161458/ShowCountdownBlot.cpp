#include "sw.h"
#include "blot.h"
#include "clock.h"
extern "C" {
void ShowCountdownBlot(SW *self, float delay) {
    BLOT *obj = (BLOT *)self->ahudblot[3].plo;
    if (obj != 0) {
        obj->field_0x8C = 0;
        obj->Select(-1);
    }
    self->tEmit = g_2dded0.t + delay;
}
}
