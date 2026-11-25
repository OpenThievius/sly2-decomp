#include "streamamb.h"
extern "C" void SetAmbGrf(STREAMAMB *, int, int);
extern "C" void ContinueAmb(STREAMAMB *);
extern "C" void OnStreamAmbStarted(int started, s64 handle)
{
    STREAMAMB *amb = (STREAMAMB *)(int)handle;
    amb->voice = started;
    if (started) {
        SetAmbGrf(amb, 0x1000, 0x1000);
    } else {
        ContinueAmb(amb);
        amb->fPending = 0;
        if (!(amb->grf & 8))
            amb->Slot7();
    }
    amb->Release();
}
