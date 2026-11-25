// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "so.h"
struct SOPROP : SO {
    u8 unknown_0x150[0x4];
    s32 cid;
    f32 field_0x158;
    f32 field_0x15C;
    u8 unknown_0x160[0x18];
    s32 field_0x178;
    u8 unknown_0x17C[0x8];
    s32 field_0x184;
};
extern "C" void InitSo(SO *);
extern "C" void func_00229EF0(SOPROP *so)
{
    InitSo(so);
    so->cid = 0x32;
    so->field_0x158 = 300.0f;
    so->field_0x15C = 500.0f;
    so->field_0x178 = -1;
    so->field_0x184 = -1;
    u32 grf = so->grfSw;
    if ((grf ^ 1) & 1)
        so->pgrfentry->grf |= 0xA;
    else
        so->grfSw = grf | 0xA;
    so->grfso &= (~0UL ^ (1UL << 35));
}
