// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "jt.h"
#include "clock.h"
#include "cm.h"

struct LIMITS {
    f32 lo;
    f32 hi;
};
struct POLY3 {
    f32 c0;
    f32 c1;
    f32 c2;
};
extern "C" {
void GetSoCpdefi__FP2SOfP6CPDEFI(JT *, CPDEFI *);
QW PosLoWorld(JT *);
float GSmooth__FfffP3SMPPf(void *, int, float, float, float);
QW PosSmooth(QW, QW, void *, int, float);
void GetAttachCpdefi(void *, CPDEFI *);
int func_0019C8B0(void *, CPDEFI *);
int bevy_player_p7_damage_1a2160(void *, CPDEFI *);
extern char D_002BCCB8[];
extern char D_002BCCC8[];
extern char D_002BCCD8[];
extern float RO_002BCC98;
extern float RO_002BCC9C;
extern float RO_002BCCA0;
extern float RO_002BCCA4;
extern float RO_002BCCA8;
extern float RO_002BCCAC;
extern float RO_002BCCB0;
extern float RO_002BCCB4;
extern POLY3 D_002BCCF0;
extern QW g_2a2dd0;
extern LIMITS g_2bbb60;
static inline float GClamp(float g, float lo, float hi)
{
    if (g < lo)
        return lo;
    if (hi < g)
        return hi;
    return g;
}
/* JT slot 50 (GetCpdefi) */
void GetJtCpdefi(JT *pjt, CPDEFI *pcpdefi) {
    float sp[4];
    GetSoCpdefi__FP2SOfP6CPDEFI(pjt, pcpdefi);
    if (pjt->fLook != 0) {
        pcpdefi->pos = pjt->look;
        pjt->field_0x104C = ((float *)&pjt->look)[2];
    } else {
        QW pos = PosLoWorld(pjt);
        float z = LaneZInGeneralRegister(pos);
        pjt->Slot97(sp);
        float lo, hi;
        if (pjt->field_0x434 != 0) {
            lo = RO_002BCCA0;
            hi = RO_002BCCA4;
        } else if (pjt->jmpState == 0x16) {
            lo = RO_002BCCB0;
            hi = RO_002BCCB4;
        } else {
            lo = RO_002BCCA8;
            hi = RO_002BCCAC;
        }
        float value = GClamp(sp[2], z + lo, z + hi);
        pjt->field_0x104C = value;
        if (B_002DDF40.fCut != 0 || B_002DDF40.psoCpdefi != pjt) {
            ((f32 *)&pcpdefi->pos)[2] = value;
        } else {
            void *table = pjt->field_0x434 != 0 ? (void *)D_002BCCC8 : (void *)D_002BCCB8;
            float smoothed = GSmooth__FfffP3SMPPf(table, 0, pjt->field_0x1050, pjt->field_0x104C, g_2dded0.dt);
            float floor = z + RO_002BCC98;
            float ceiling = z + RO_002BCC9C;
            ((f32 *)&pcpdefi->pos)[2] = smoothed;
            float clamped;
            if (smoothed < floor) {
                clamped = floor;
            } else {
                if (ceiling < smoothed)
                    clamped = ceiling;
                else
                    clamped = smoothed;
            }
            ((f32 *)&pcpdefi->pos)[2] = clamped;
        }
        ((f32 *)&pcpdefi->pos)[0] = sp[0];
        ((f32 *)&pcpdefi->pos)[1] = sp[1];
    }
    {
        QW smoothed = PosSmooth(pjt->dir, g_2a2dd0, D_002BCCD8, 0, g_2dded0.dt);
        pjt->dir = smoothed;
        QW sum = VectorAdd(pcpdefi->pos, smoothed);
        pcpdefi->pos = sum;
        pjt->look = sum;
    }
    pjt->field_0x1050 = ((f32 *)&pcpdefi->pos)[2];
    if (pjt->jmpState != -1) func_0019C8B0(pjt->PvJmp(), pcpdefi);
    if (pjt->field_0x4CC != -1) GetAttachCpdefi(pjt->PvAttach(), pcpdefi);
    if (pjt->zapState != -1) bevy_player_p7_damage_1a2160(pjt->PvZap(), pcpdefi);
    {
        QW vec = pjt->Slot34();
        float length = LaneX(SqrtX(SquaredLength(vec)));
        float t = D_002BCCF0.c0 + length * (D_002BCCF0.c1 + length * D_002BCCF0.c2);
        float tLow = g_2bbb60.lo;
        float tHigh = g_2bbb60.hi;
        if (t < tLow) {
            t = tLow;
        } else if (tHigh < t) {
            t = tHigh;
        }
        pcpdefi->sAdjust = pcpdefi->sAdjust * t;
    }
}
}
