/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void InitGuard(void);

/* The sensor object a guard owns (STEPGUARD::psensor, include/guard.h SENSOR); only the word this init sets is named. */
struct SENSORVIEW {
    u8 unknown_0x0[0xF8];
    s32 field_0xF8;
};

/* Three words at 0x1070 of the guard that this init sets together. */
struct GUARDTUNING {
    f32 field_0x0;
    f32 field_0x4;
    s32 field_0x8;
};

/* The part of a guard (STEPGUARD, include/stepguard.h, C++ only) that this class's init sets after InitGuard. */
struct GUARDVIEW {
    u8 unknown_0x0[0x364];
    s32 field_0x364;
    u8 unknown_0x368[0x13C];
    s32 field_0x4A4;
    u8 unknown_0x4A8[0x9BC];
    s32 sensing;
    u8 unknown_0xE68[0xFC];
    struct SENSORVIEW *psensor;
    u8 unknown_0xF68[0x108];
    struct GUARDTUNING tuning;
    u8 unknown_0x107C[0x4];
    f32 field_0x1080;
    f32 field_0x1084;
    f32 field_0x1088;
};

void func_001B9F80(struct GUARDVIEW *pguard) {
    struct GUARDTUNING *ptuning;

    InitGuard();
    ptuning = &pguard->tuning;
    ptuning->field_0x0 = 1.35f;
    ptuning->field_0x4 = -0.0003f;
    ptuning->field_0x8 = 0;
    pguard->field_0x1080 = 0.9f;
    pguard->field_0x1084 = 1.2f;
    pguard->field_0x1088 = 7.0f;
    pguard->field_0x364 = 0;
    pguard->sensing = 0;
    pguard->psensor->field_0xF8 = 3;
    pguard->field_0x4A4 = 1;
}
