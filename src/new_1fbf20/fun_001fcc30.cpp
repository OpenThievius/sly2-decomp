#include "amb.h"
extern "C" {
void ContinueAmb(AMB *);
void SetAmbGrf(AMB *, int, int);
void func_001FCC30(int flag, s64 arg1) {
    AMB *self = (AMB *)(int)arg1;
    if (flag != 0) {
        self->fPending = 0;
        ContinueAmb(self);
    } else {
        SetAmbGrf(self, 0x1000, 0x1000);
    }
    self->Release();
}
}
