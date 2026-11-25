// SPDX-License-Identifier: GPL-3.0-or-later
#include "murray.h"
extern "C" const float g_2dded0;
extern "C" void GetJtCpdefi(MURRAY *, unsigned *);
extern "C" void func_00220388(void *, unsigned *);
extern "C" void func_0019EA00(void *, unsigned *);

void GetMurrayCpdefi(MURRAY *murray, unsigned *flags)
{
    if (murray->state != 0) {
        if (murray->state != 0x10) {
            if (murray->field_0x4CC != 0)
                murray->field_0x1080 = g_2dded0;
        }
    }
    GetJtCpdefi(murray, flags);
    switch (murray->state) {
    case 11:
        if (murray->focusKind != 4) break;
    case 3:
    case 9:
    case 12:
        *flags |= 1;
        break;
    case 15:
        func_00220388(murray->PvCarry(), flags);
        break;
    case 20:
        func_0019EA00(murray->PvPipe(), flags);
        break;
    }
}
