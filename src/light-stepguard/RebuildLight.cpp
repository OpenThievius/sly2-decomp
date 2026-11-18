// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "lo.h"

struct BYTES8 {
    char bytes[8];
};
struct BYTES12 {
    BYTES8 first;
    int second;
};

struct LIGHT : LO {
    u8 unknown_0x50[0x90];
    /* 0xE0 */ s32 mode;
    u8 unknown_0xE4[0xC];
    /* 0xF0 */ VECTOR hsv;
    /* 0x100 */ VECTOR pos;
    /* 0x110 */ float scaleA;
    /* 0x114 */ float scaleB;
    u8 unknown_0x118[8];
    /* 0x120 */ s32 modeCopy;
    /* 0x124 */ float angleA;
    /* 0x128 */ float angleB;
    /* 0x12C */ float fitA;
    /* 0x130 */ float color[3];
    /* 0x13C */ float alpha;
    /* 0x140 */ BYTES12 posCopy;
    /* 0x14C */ float fitB;
    /* 0x150 */ float strength;
    /* 0x154 */ float cone;
    u8 unknown_0x158[0xC];
    /* 0x164 */ float rangeA;
    /* 0x168 */ float rangeB;
};

extern "C" {
void ConvertAngleStrength__FffffPfT4(float, float, float, float, float *, float *);
void ConvertUserHsvToUserRgb__FP6VECTORT0(VECTOR *, VECTOR *);
void GreyColor_1ed2d8(VECTOR *);
QW PosLoWorld(void *);
void FitLinearFunction__FffffPfT4(float, float, float, float, float *, float *);
void func_001A3B38(void *);

void RebuildLight(LIGHT *light)
{
    VECTOR rgb;
    float strengthFirst = light->strength;
    float limit = light->hsv.z < strengthFirst ? strengthFirst : light->hsv.z;
    float cone = light->cone > 30.0f ? light->cone : 30.0f;
    ConvertAngleStrength__FffffPfT4(cone, 0.0f, 0.0f, limit, &light->angleA, &light->angleB);
    ConvertUserHsvToUserRgb__FP6VECTORT0(&light->hsv, &rgb);
    GreyColor_1ed2d8(&rgb);
    float red = rgb.x;
    float green = rgb.y;
    float blue = rgb.z;
    light->color[0] = red;
    light->color[1] = green;
    light->color[2] = blue;
    light->alpha = light->strength;
    if (limit > 0.0f) {
        red = red / limit;
        green = green / limit;
        blue = blue / limit;
        light->alpha = light->alpha / limit;
        light->color[0] = red;
        light->color[1] = green;
        light->color[2] = blue;
    }
    light->angleB = -light->angleB;
    light->modeCopy = light->mode;
    switch (light->mode) {
    case 0: {
        VECTOR *pos = &light->pos;
        pos->z = 0.0f;
        pos->y = 0.0f;
        light->scaleA = 1.0f;
        light->pos.x = 0.0f;
        light->scaleB = 0.0f;
        light->posCopy = *(BYTES12 *)light->PmatWorld();
        break;
    }
    case 1:
        *(QW *)&light->pos = PosLoWorld(light);
        light->posCopy = *(BYTES12 *)&light->pos;
        FitLinearFunction__FffffPfT4(light->rangeA, 1.0f, light->rangeB, 0.0f, &light->fitA, &light->fitB);
        light->scaleA = light->fitA;
        light->scaleB = light->fitB;
        break;
    }
    float hsvLast = light->hsv.z;
    limit = light->strength < hsvLast ? hsvLast : light->strength;
    light->scaleA = light->scaleA * limit;
    light->scaleB = light->scaleB * limit;
    func_001A3B38(light);
}
}
