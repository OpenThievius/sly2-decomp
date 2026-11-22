// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
extern "C" void InitJt(JT *);
extern "C" void func_0020B840(void *, void *, int);
extern "C" void bevy_player_p25_default(void *, void *);
extern "C" void Carry_Init(void *);
extern "C" void SetStepSpinRatio__FP4STEPf(STEP *, float);
extern "C" SLY *g_2e1e40;
// the four words from 0x10A8 that InitSly sets (JT fields 0x10A8 to 0x10B4), reached through one pointer
struct TAIL10A8 { f32 field_0x0; s32 field_0x4; f32 field_0x8; f32 field_0xC; };
extern "C" void InitSly(SLY *sly)
{
    InitJt(sly);
    sly->rBounds = 15.0f;
    sly->jts = -1;
    sly->jtcs = -1;
    sly->field_0x18D0 = -1;
    func_0020B840(sly->PvPart1320(), sly, 0x6F);
    func_0020B840(sly->PvPart1C30(), sly, 0x6F);
    TAIL10A8 *tail = (TAIL10A8 *)&sly->field_0x10A8;
    sly->field_0x1098 = -100.0f;
    sly->field_0x109C = 100.0f;
    sly->field_0x10A0 = 50.0f;
    sly->field_0x10A4 = -10.0f;
    sly->field_0x10A8 = 250.0f;
    tail->field_0x8 = 1.0f;
    tail->field_0x4 = 0;
    tail->field_0xC = 4500.0f;
    SetStepSpinRatio__FP4STEPf(sly, 1.6f);
    sly->field_0x1FB0 = 0x1A;
    sly->field_0x1FBC = 0x25;
    sly->field_0x1FC8 = 0x26;
    sly->field_0x1FD4 = 0x29;
    bevy_player_p25_default(sly->PvPart1FF0(), sly);
    sly->field_0x1000 = 1;
    sly->field_0x1020 = 200.0f;
    sly->keyHull = 0xC7;
    Carry_Init(sly->carry);
    g_2e1e40 = sly;
}
