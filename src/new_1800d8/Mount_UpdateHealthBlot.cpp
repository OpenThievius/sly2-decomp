#include "mount.h"
extern "C" void SeekBlotLabel(void*, int, float);
extern "C" void Mount_UpdateHealthBlot(MOUNT* self)
{
    if (self->pblot) {
        int hp = self->hp;
        if (hp < 1) hp = 0;
        float lost = 1.0f - (float)hp / (float)self->hpMax;
        if (lost < 0.0f) lost = 0.0f;
        else if (1.0f < lost) lost = 1.0f;
        SeekBlotLabel(self->pblot, 0x34F, lost);
    }
}
