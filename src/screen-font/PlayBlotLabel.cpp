#include "blot.h"
extern "C" {
void PlayRootSpriteLabel(int);
void SetBlotModal(void *, int);
void PlayBlotLabel(BLOT *self, int arg1) {
    PlayRootSpriteLabel(self->asprite);
    self->Slot21(1);
    if (self->modal != 0) {
        SetBlotModal(self, 0);
    }
    self->cur = arg1;
}
}
