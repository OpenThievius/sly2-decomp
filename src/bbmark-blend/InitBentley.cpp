// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
extern "C" void InitJt(JT *);
extern "C" void func_0020B840(void *, void *, int);
extern "C" void *g_2dd5bc;
extern "C" void InitBentley(BENTLEY *p)
{
    InitJt(p);
    // BEGIN
    p->state = -1;
    p->field_0x16B0 = -1;
    p->field_0x1040 = 0;
    p->aimState = -1;
    p->field_0x1800 = -1;
    p->field_0x103C = 45.0f;
    p->field_0x1048 = 125.0f;
    func_0020B840(p->PvBlendState1(), p, 0x73);
    func_0020B840(p->PvBlendState7(), p, 0x73);
    p->field_0x3D8 = -70.0f;
    p->field_0x1098 = -100.0f;
    p->field_0x109C = 100.0f;
    p->field_0x10A0 = 50.0f;
    p->field_0x10A4 = -10.0f;
    p->field_0x10A8 = 250.0f;
    f32 *pfloatsAt10A8 = &p->field_0x10A8;
    pfloatsAt10A8[2] = 1.0f;
    *(s32 *)&pfloatsAt10A8[1] = 0;
    pfloatsAt10A8[3] = 4500.0f;
    p->field_0x1000 = 2;
    p->aslot[1].gadget = 7;
    p->aslot[2].gadget = 9;
    p->aslot[3].gadget = 0xB;
    p->aslot[4].gadget = 0xD;
    p->aslot[5].gadget = 4;
    p->aslot[0].gadget = 5;
    p->field_0x1870 = 5;
    // END
    g_2dd5bc = p;
}
