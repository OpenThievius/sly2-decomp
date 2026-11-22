// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "so.h"
/* One reader on a class-0x31 object: func_0020E2B0 reads SO word 0xC8. Not in so.h. */
struct SOVALUE { u8 unknown_0x0[0xC8]; /* 0xC8 */ s32 field_0xC8; };
struct LEVEL { char pad[0x3E5C]; int value; void *plo; };
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
        plevel->value = ((SOVALUE *)pbest)->field_0xC8;
        SetLoGrfzon(pbest, 0xFF);
    }
}
