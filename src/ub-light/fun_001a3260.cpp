// SPDX-License-Identifier: GPL-3.0-or-later
#include "light.h"
#include "ps2inline.h"
struct M3 { QW row[3]; };
/* the global light list: B_003E04F8 is its head and each light links the next at 0x20, inside LO's unknown bytes (0x24 is
   the sibling link of the parent's children, retail reads 0x20 here) */
struct LIGHTLISTNODE {
    u8 unknown_0x0[0x20];
    /* 0x20 */ LIGHT *plightNext;
};
extern LIGHT *B_003E04F8;
extern QW g_2a2dc0;
extern "C" {
void *PloNew(int, int, int, int);
void BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3(M3 *, QW, QW);
void func_001A3610(LIGHT *, float);
void func_001A3630(LIGHT *, float);
}
extern "C" void func_001A3260()
{
    LIGHT *plight = B_003E04F8;
    while (plight && plight->fDynamic != 0)
        plight = ((LIGHTLISTNODE *)plight)->plightNext;
    if (plight) return;
    plight = (LIGHT *)PloNew(4, 0, 0x188, -1);
    struct L { M3 copy; QW dir; M3 mat; } l;
    QW dir = VectorFromFloats3(-0.2f, 0.3f, -1.0f);
    l.dir = dir;
    BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3(&l.mat, dir, g_2a2dc0);
    l.copy = l.mat;
    plight->Slot30(&l.copy);
    func_001A3610(plight, 255.0f);
    func_001A3630(plight, 240.0f);
}
