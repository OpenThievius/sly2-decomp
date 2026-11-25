#include "sly.h"
#include "clock.h"
extern "C" void SetClockRate(void *, int, float);
extern "C" void StopAmb(void *, float);
extern "C" void VirtualRefPtr_Assign(void *, void *);
extern "C" void func_00141E28(void *);
extern float g_3e1bec;

extern "C" void ReleaseSlyGadget(SLY *sly, int gadget)
{
    if (gadget == 0x1D || gadget == 0x2A) {
        SetClockRate(&g_2dded0, 1, 1.0f);
        void **slot = &sly->pemitter;
        if (*slot != 0) {
            StopAmb(*slot, 0.0f);
            VirtualRefPtr_Assign(slot, 0);
        }
        g_3e1bec = 0.0f;
    } else {
        func_00141E28(sly);
    }
}
