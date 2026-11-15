// SPDX-License-Identifier: GPL-3.0-or-later
// 0x18E540 SetJtJtcs
#include "types.h"
#include "sly2.h"
#include "lo.h"
#include "sly.h"
#include "vu0inline.h"

struct PART : SO {
};
struct ASEG {
    u8 unknown_0x0[0x74];
    f32 tMax;
};
struct ASEGBL : ASEG {
};
struct ASEGA {
    u8 unknown_0x0[0x1C];
    f32 field_0x1C;
    u8 unknown_0x20[0x20];
    f32 field_0x40;
    u8 unknown_0x44[0x4];
    f32 field_0x48;
};
struct JTCSINFO {
    u8 unknown_0x0[0x130];
    s32 sfx;
};
struct AMB;

extern "C" void ApplyAsegToHandle(ASEG *paseg, SLY *psly, int grf, ASEGA **ppasega, float tLocal, float svt);
extern "C" void Carry_SetState(void *pcarry, int carrys);
extern "C" void ChooseJtSweepTarget__FP2JTP2BLP6ASEGBL(SLY *psly, BL *pbl, ASEGBL *pasegbl);
extern "C" QW ConvertAloPos(LO *ploFrom, LO *ploTo, QW pos);
extern "C" int IsmsFindSmOptional__FP2SM3OID(SM *psm, int oid);
extern "C" AMB *NewEmitter(int sfx);
extern "C" QW PosLoWorld(LO *plo);
extern "C" void SeekSma(void *psma, int oid);
extern "C" void SetAmbPos(AMB *pamb, QW pos);
extern "C" void SetEmitterUnpositioned(AMB *pamb, int f);
extern "C" void func_00131A90(ASEGA *pasega, float t);
extern "C" void func_001F2AD0(SLY *psly, void *pv);
extern "C" void func_001F4BF8(SO *pso);

extern "C" int B_002E1E44;
extern "C" int B_002E1E48;
extern "C" int D_002BF448[];
extern "C" float D_FLT_002BF430;
extern "C" float D_FLT_002BF434;
extern "C" float D_FLT_002BF438;
extern "C" float D_FLT_002BF43C;
extern "C" float D_FLT_002BF440;
extern "C" float g_2dded0;

extern "C" void SetJtJtcs(SLY *psly, int jtcs)
{
    int jtcsOld = psly->jtcs;
    if (jtcsOld == jtcs)
        return;

    int fKeep = 0;
    if (jtcs != -1 && jtcsOld != -1)
        fKeep = jtcs == D_002BF448[jtcsOld];
    if (fKeep == 0)
        func_001F2AD0(psly, psly->field_0x1A88);

    int sfx = -1;
    switch (psly->jtcs) {
    case -1:
        break;
    case 1:
        sfx = psly->pjtcsinfo->sfx;
        func_001F4BF8(psly);
        break;
    case 2:
        func_001F4BF8(psly);
        break;
    case 0:
        Carry_SetState(psly->carry, -1);
        break;
    }
    if (sfx != -1) {
        AMB *pamb = NewEmitter(sfx);
        SetEmitterUnpositioned(pamb, 0);
        SetAmbPos(pamb, PosLoWorld(psly));
    }

    float svt = 1.0f;
    float tLocal = 0.0f;
    ASEG *paseg = 0;
    float dt = 0.0f;
    int sfxNew = -1;
    switch (jtcs) {
    case -1:
        psly->ptarget = 0;
        break;
    case 1:
    case 2:
        func_001F4BF8(psly);
        break;
    case 10:
        func_001F4BF8(psly);
        paseg = psly->apasegHide[0];
        break;
    case 11:
        func_001F4BF8(psly);
        paseg = psly->apasegHide[1];
        break;
    case 0:
        Carry_SetState(psly->carry, 0);
        svt = 0.0f;
        paseg = psly->pasegCarry;
        sfxNew = 0xF;
        tLocal = paseg->tMax * 0.5f;
        func_001F4BF8(psly);
        psly->tJtcsNext = g_2dded0 + 0.1f;
        break;
    case 3: {
        QW posHide = ConvertAloPos(0, psly, PosLoWorld(psly->apartHide[1]));
        QW posCane = ConvertAloPos(0, psly, *(QW *)((char *)psly->paloCane + 0x70));
        VECTOR posMid;
        VECTOR scale;
        *(QW *)&scale = VectorFromFloat(0.5f);
        *(QW *)&posMid = BlendX(*(QW *)&scale, posHide, *(QW *)&scale, posCane);
        if (psly->jts == 0) {
            jtcs = 6;
            if (B_002E1E44 != 0)
                goto sweep6;
            jtcs = 7;
            if (B_002E1E48 != 0)
                goto sweep7;
            jtcs = 6;
            if (posMid.y < 0.0f)
                goto sweep6;
            jtcs = 7;
            goto sweep7;
        }
        jtcs = 4;
        if (B_002E1E44 != 0)
            goto sweep4;
        jtcs = 5;
        if (B_002E1E48 != 0)
            goto sweep5;
        jtcs = 4;
        if (posMid.y < 0.0f)
            goto sweep4;
        jtcs = 5;
        goto sweep5;
    }
    case 4:
    sweep4:
        sfxNew = 0xB;
        ChooseJtSweepTarget__FP2JTP2BLP6ASEGBL(psly, &psly->asweep[0].bl, psly->asweep[0].pasegbl);
        dt = D_FLT_002BF430;
        paseg = psly->asweep[0].pasegbl;
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF434;
        break;
    case 5:
    sweep5:
        sfxNew = 0xB;
        ChooseJtSweepTarget__FP2JTP2BLP6ASEGBL(psly, &psly->asweep[1].bl, psly->asweep[1].pasegbl);
        dt = D_FLT_002BF430;
        paseg = psly->asweep[1].pasegbl;
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF438;
        break;
    case 6:
    sweep6:
        sfxNew = 0xB;
        ChooseJtSweepTarget__FP2JTP2BLP6ASEGBL(psly, &psly->asweep[2].bl, psly->asweep[2].pasegbl);
        dt = D_FLT_002BF430;
        paseg = psly->asweep[2].pasegbl;
        if (IsmsFindSmOptional__FP2SM3OID(psly->psm, 0x17B) >= 0)
            SeekSma(psly->field_0x1034, 0x17B);
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF434;
        break;
    case 7:
    sweep7:
        sfxNew = 0xB;
        ChooseJtSweepTarget__FP2JTP2BLP6ASEGBL(psly, &psly->asweep[3].bl, psly->asweep[3].pasegbl);
        dt = D_FLT_002BF430;
        paseg = psly->asweep[3].pasegbl;
        if (IsmsFindSmOptional__FP2SM3OID(psly->psm, 0x17B) >= 0)
            SeekSma(psly->field_0x1034, 0x17B);
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF438;
        break;
    case 8:
        paseg = psly->pasegJtcs8;
        break;
    case 9:
        paseg = psly->pasegJtcs9;
        break;
    case 12:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[0];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        if (psly->jts == 0 && IsmsFindSmOptional__FP2SM3OID(psly->psm, 0x17B) >= 0)
            SeekSma(psly->field_0x1034, 0x17B);
        break;
    case 13:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[1];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        if (psly->jts == 0 && IsmsFindSmOptional__FP2SM3OID(psly->psm, 0x17B) >= 0)
            SeekSma(psly->field_0x1034, 0x17B);
        break;
    case 14:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[2];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        break;
    case 15:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[3];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        break;
    case 16:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[4];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        break;
    case 17:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[5];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        break;
    case 18:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[6];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        break;
    case 19:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[7];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        break;
    case 20:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[8];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        break;
    case 21:
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 1;
        paseg = psly->apasegJtcs[9];
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        break;
    case 22:
    case 23:
        if (jtcs == 22)
            paseg = psly->apasegJtcs[13];
        else
            paseg = psly->apasegJtcs[14];
        dt = D_FLT_002BF43C;
        psly->field_0x18EC = 0;
        psly->tJtcsNext = g_2dded0 + D_FLT_002BF440;
        if (psly->jts == 0 && IsmsFindSmOptional__FP2SM3OID(psly->psm, 0x17B) >= 0)
            SeekSma(psly->field_0x1034, 0x17B);
        break;
    }

    if (fKeep != 0) {
        ASEGA *pasega = psly->pasegaJtcs;
        sfxNew = -1;
        svt = pasega->field_0x40 / pasega->field_0x48;
        float tA = pasega->field_0x1C;
        float tB = paseg->tMax;
        tLocal = tA < tB ? tA : tB;
    } else {
        psly->field_0x18E4 = 0;
    }

    int fHideOld = 0;
    if (psly->jtcs == 11 || psly->jtcs == 2)
        fHideOld = 1;
    int fHideNew = 0;
    if (jtcs == 11 || jtcs == 2)
        fHideNew = 1;
    if (fHideOld != fHideNew) {
        if (jtcs == 11 || jtcs == 2) {
            psly->apartHide[2]->Add();
            psly->apartHide[2]->SetPosMatFromLo(psly->apartHide[0]);
            psly->apartHide[0]->Remove();
        } else {
            psly->apartHide[0]->Add();
            psly->apartHide[0]->SetPosMatFromLo(psly->apartHide[2]);
            psly->apartHide[2]->Remove();
        }
    }

    psly->jtcs = jtcs;
    psly->cbounds = 0;
    psly->tJtcs = g_2dded0;
    ApplyAsegToHandle(paseg, psly, 1, &psly->pasegaJtcs, tLocal, svt);
    if (dt != 0.0f)
        func_00131A90(psly->pasegaJtcs, g_2dded0 + dt);
    if (sfxNew != -1) {
        AMB *pamb = NewEmitter(sfxNew);
        SetEmitterUnpositioned(pamb, 0);
        SetAmbPos(pamb, PosLoWorld(psly));
    }
}
