// SPDX-License-Identifier: GPL-3.0-or-later
#include "dancer.h"

// the camera's focus record (src/so/GetSoCpdefi__FP2SOfP6CPDEFI.cpp names radHome); only the angle is read here
struct CPDEFI {
    u8 unknown_0x0[0x30];
    f32 radHome;
};

void GetSoCpdefi__FP2SOfP6CPDEFI(DANCER *, CPDEFI *);

void GetDancerCpdefi(DANCER *dancer, CPDEFI *pcpdefi) {
    GetSoCpdefi__FP2SOfP6CPDEFI(dancer, pcpdefi);
    pcpdefi->radHome = (f32) (pcpdefi->radHome - 2.3561945f);
}
