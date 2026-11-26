#include "murray.h"
// SPDX-License-Identifier: GPL-3.0-or-later
// InitMurray: retail stores 0x220 and 0x17F4 before the other float stores, and 0x1434 before the 0x1098 group.
// gcc 2.95's first scheduler ranks a store that is the last use of its constant (REG_DEAD, weight -1) ahead of one that is not,
// then by source order: the -1 stores are written with 0x17F4 last (the one that kills the constant), before the float stores,
// and the -60 store to 0x1AC8 comes before the one to 0x1434 so that 0x1434 is the dying use and is emitted first.
/* the tail of the tuning block at JT 0x10A8 (field_0x10A8, field_0x10AC, field_0x10B0, field_0x10B4), seen from its start */
struct JTTUNING {
    f32 field_0x0;
    s32 field_0x4;
    f32 field_0x8;
    f32 field_0xC;
};
extern "C" void InitJt(JT *);
extern "C" void func_0020B840(void *, void *, int);
extern "C" void func_0020BD78(void *);
extern "C" void CarryThrow_Init(void *, void *);
extern "C" void *g_2f7900;
extern "C" void InitMurray(MURRAY *murray)
{
    InitJt(murray);
    murray->field_0x220 = 50.0f;
    murray->field_0x13D8 = -1;
    murray->field_0x1810 = -1;
    murray->field_0x1840 = -1;
    murray->state = -1;
    murray->field_0x144C = -1;
    murray->field_0x1450 = -1;
    murray->iapasegByIndex = -1;
    murray->field_0x17F4 = -1;
    murray->field_0x1410 = 1500.0f;
    murray->field_0x1414 = 3500.0f;
    murray->field_0x103C = 60.0f;
    murray->field_0x1048 = 125.0f;
    func_0020B840(murray->runBlendA, murray, 0x15);
    func_0020B840(murray->runBlendCarry, murray, 0x15);
    func_0020B840(murray->runBlendD, murray, 0x15);
    func_0020B840(murray->runBlendC, murray, 0x15);
    func_0020BD78(murray->part1850);
    JTTUNING *tuning = (JTTUNING *)&murray->field_0x10A8;
    murray->field_0x1AC8 = -60.0f;
    murray->field_0x1434 = -60.0f;
    murray->field_0x1098 = -100.0f;
    murray->field_0x109C = 100.0f;
    murray->field_0x10A0 = 50.0f;
    murray->field_0x10A4 = -10.0f;
    murray->field_0x10A8 = 250.0f;
    tuning->field_0x8 = 1.0f;
    tuning->field_0x4 = 0;
    tuning->field_0xC = 4500.0f;
    CarryThrow_Init(murray->PvCarry(), murray);
    murray->field_0x1000 = 4;
    g_2f7900 = murray;
}
