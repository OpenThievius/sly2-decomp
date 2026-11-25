// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
#include "sndsystem.h"
extern SNDSYSTEM B_003DD040;
extern "C" {
void func_002330D0(int, int, int, int, int, int, int, void *, s64);
void func_001FCC30();
void OnAmbVoicePolled();
}
void SetAmbGrf(AMB *, int, int);
void func_001FC878(AMB *pamb)
{
    if (pamb->grf & 0x1000) {
        pamb->AddRef();
        func_002330D0(0x524B5553, 7, pamb->voice, 0, 0, 0, 0, (void *)func_001FCC30, (s64)pamb);
        SetAmbGrf(pamb, 0x1000, 0);
    }
    if ((u16)pamb->fPending == 0) {
        if (pamb->grf & 0x400) {
            pamb->AddRef();
            func_002330D0(0x524B5553, 8, pamb->voice, 0, 0, 0, 0, (void *)OnAmbVoicePolled, (s64)pamb);
            SetAmbGrf(pamb, 0x400, 0);
        }
        if ((pamb->grf & 0x800) && pamb->cPause < 1)
            pamb->played += B_003DD040.now - B_003DD040.prev;
    }
}
