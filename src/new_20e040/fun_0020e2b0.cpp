// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
struct LEVEL { u8 unknown_0x0[0x3E5C]; int value; void *plo; };
extern "C" int CploFindSwObjectsByClass(LEVEL *, int, int, int, int, SO **);
extern "C" void SetLoGrfzon(SO *, int);

void func_0020E2B0(LEVEL *plevel)
{
    SO *apso[16];
    int count = CploFindSwObjectsByClass(plevel, 5, 0x31, 0, 16, apso);
    int best = 0;
    SO *pbest = 0;
    int i;
    for (i = 0; i < count; i++) {
        SO *pso = apso[i];
        if (best < pso->field_0xB8) {
            best = pso->field_0xB8;
            pbest = pso;
        }
    }
    if (pbest) {
        plevel->value = pbest->field_0xC8;
        SetLoGrfzon(pbest, 0xFF);
    }
}
