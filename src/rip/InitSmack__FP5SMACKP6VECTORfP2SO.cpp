/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
struct SO; struct CM; struct RIP;
struct VEC3_1D04E8 { float x, y, z; };
struct SMACKI_1D04E8 { u8 unknown_0x0[0x20]; float vmin[3]; u8 unknown_0x2C[0x4]; float vmax[3]; u8 unknown_0x3C[0x14]; QW scale; };
struct SMACK_1D04E8 { u8 unknown_0x0[0x18]; float lifetime; u8 unknown_0x1C[0x4]; QW scale; QW alpha; u8 unknown_0x40[0x50]; VEC3_1D04E8 v; u8 unknown_0x9C[0x54]; SMACKI_1D04E8 *table; u8 unknown_0xF4[0xC]; QW screen; };
extern "C" float GRandInRange(float, float);
extern "C" QW ConvertCmWorldToScreen(CM *, QW);
extern "C" void InitRip__FP3RIPP6VECTORfP2SO(RIP *, QW, float, SO *);
extern CM B_002DDF40;
extern QW D_002BBB50;
extern float D_002C2000;
static inline void SetVec_1D04E8(VEC3_1D04E8 *p, float x, float y, float z) { p->x = x; p->y = y; p->z = z; }
extern "C" void InitSmack__FP5SMACKP6VECTORfP2SO(SMACK_1D04E8 *smack, QW pos, float scale, SO *so)
{
    InitRip__FP3RIPP6VECTORfP2SO((RIP *)smack, pos, scale, so);
    SMACKI_1D04E8 *table = smack->table;
    smack->screen = ConvertCmWorldToScreen(&B_002DDF40, pos);
    float vx = GRandInRange(table->vmin[0], table->vmax[0]);
    float vy = GRandInRange(table->vmin[1], table->vmax[1]);
    float vz = GRandInRange(table->vmin[2], table->vmax[2]);
    SetVec_1D04E8(&smack->v, vx, vy, vz);
    smack->lifetime = D_002C2000;

    smack->alpha = D_002BBB50;
    smack->scale = table->scale;
}
