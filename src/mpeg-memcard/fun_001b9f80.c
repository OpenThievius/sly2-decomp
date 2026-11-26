/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "guardview.h"

void InitGuard(void);

/* Three words at 0x1070 of the guard that this init sets together. */
struct GUARDTUNING {
    f32 field_0x0;
    f32 field_0x4;
    s32 field_0x8;
};

/* The guard this class's init sets after InitGuard (the class of mpeg_memcard_1ba0b8.cpp's ZONEGUARD, same offsets): a STEPGUARD (the C view, guardview.h) up to its 0x1010 bytes, then the class's own words. */
struct GUARDVIEW {
    struct STEPGUARDVIEW guard;
    u8 unknown_0xFE0[0x1070 - 0xFE0];
    struct GUARDTUNING tuning; /* ZONEGUARD::curve (mpeg_memcard_1ba0b8.cpp, UpdateZoneScriptBeh): the distance quadratic, as three words */
    u8 unknown_0x107C[0x4];
    f32 lowLimit;       /* ZONEGUARD::lowLimit */
    f32 highLimit;      /* ZONEGUARD::highLimit */
    f32 reach;          /* ZONEGUARD::reach */
};

void func_001B9F80(struct GUARDVIEW *pguard) {
    struct GUARDTUNING *ptuning;

    InitGuard();
    ptuning = &pguard->tuning;
    ptuning->field_0x0 = 1.35f;
    ptuning->field_0x4 = -0.0003f;
    ptuning->field_0x8 = 0;
    pguard->lowLimit = 0.9f;
    pguard->highLimit = 1.2f;
    pguard->reach = 7.0f;
    pguard->guard.field_0x364 = 0;
    pguard->guard.sensing = 0;
    pguard->guard.psensor->grfSensing = 3;
    pguard->guard.field_0x4A4 = 1;
}
