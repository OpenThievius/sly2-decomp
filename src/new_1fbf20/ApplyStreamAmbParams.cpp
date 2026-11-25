#include "streamamb.h"
extern "C" void func_00233088(int, int, int, int, int, int, int);
void ApplyStreamAmbParams(STREAMAMB *pamb)
{
    unsigned grf = pamb->grf;
    if (grf & 0x70) {
        int param = 0;
        int vol;
        int pitch;
        if (grf & 0x10) {
            param = 1;
            vol = (int)(pamb->volAudible * 1024.0f);
        }
        if (grf & 0x20) param |= 4;
        if (grf & 0x40) {
            param |= 8;
            pitch = (int)(pamb->pitch * 12.0f);
        }
        func_00233088(0x524B5553, 5, pamb->voice, param, vol, pamb->pan, pitch);
    }
    if (pamb->grf & 0x180) {
        int slot;
        unsigned one;
        for (slot = 0, one = 1; slot < 6; slot++) {
            if (pamb->mask & (one << slot))
                func_00233088(0x524B5553, 6, pamb->voice, slot, (int)(pamb->vol[slot] * 1024.0f), pamb->slotPan[slot], 0);
        }
        pamb->mask = 0;
    }
}
