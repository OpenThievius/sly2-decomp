#include "streamamb.h"
extern "C" {
void func_001FB0C0(void *);
void ReplayStreamAmb(STREAMAMB *self) {
    int active = 0; if (self->voice == 0) { int x = self->fPending != 0 || (self->grf & 1) != 0; active = x ^ 1; } if (active) {
        func_001FB0C0(self);
        self->played = 0;
        self->mask = 0xF;
    }
}
}
