// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jt.h"
#include "cm.h"
extern "C" void func_0019E9D8(void *);
extern "C" QW PosLoWorld(JT *);
void func_00141588(JT *pjt, VECTOR *ppos)
{
    if (pjt->field_0xF54 != -1) {
        func_0019E9D8(&pjt->field_0xF50);
        return;
    }
    *(QW *)ppos = PosLoWorld(pjt);
    float z;
    if (pjt->psoSurface != 0) {
        z = pjt->vecWorld.z + pjt->field_0x1048;
    } else {
        if (pjt->jmpState == 0x14 || B_002DDF40.fCut != 0 || B_002DDF40.psoCpdefi != pjt) {
            ppos->z = ppos->z + (pjt->vecLocal.z + pjt->field_0x1048);
            return;
        }
        z = pjt->field_0x104C;
    }
    ppos->z = z;
}
