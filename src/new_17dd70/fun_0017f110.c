/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* the part of SOHIT (sohit.h, C++ only) this function writes; same offset */
struct SOHITVIEW {
    u8 unknown_0x0[0x18C];
    s32 fTouchQueued;
};

void RemoveSoLoHierarchy(struct SOHITVIEW *pso);

void func_0017F110(struct SOHITVIEW *pso) {
    RemoveSoLoHierarchy(pso);
    pso->fTouchQueued = 0;
}
