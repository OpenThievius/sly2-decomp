// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "bentley.h"
#include "gadgetobj.h"
#include "asega.h"
#include "xf.h"
#include "clock.h"
extern "C" {
extern QW g_2a2dd0;
void SetXfKind(void *, XF *, int);
void ScheduleJtGlance(void *);
void ExplodeExpl(void *);
void SetJmpBodyState(void *, int, int);
void SetAttachSubstate(void *, int);
void SetJtZapState(void *, int);
void SetJtPipeState(void *, int);
void ReleaseBentleyGadget(void *);
void SetBentleyGadgetAnim(void *, int);
void func_00136530(void *, int);
void CarryThrow_SetState(void *, int);
int IsmsFindSmOptional__FP2SM3OID(SM *, int);
int func_001430C8(void *);
void func_00142868(void *, int);
void ResetRunBlendFootsteps(void *);
void SetBinocState(void *, int);
void RetractAsegaHandle(void *);
void RetractSmaRef(void *);
void ApplyAsegToHandle(void *, void *, int, void *, float, float);
void func_001F14F8(void *, void *, int, int, int, void *);
}

/* the animations and objects SetBentleyState picks per state: a view of BENTLEY (one reader each, and SetBentleyState is not in the class's vtable) */
struct BENTLEYSTATEANIMS {
    u8 unknown_0x0[0x1A0];
    /* 0x1A0 */ f32 field_0x1A0; /* STEP's word: the phase of the run animation, kept when leaving state 1 or 7 and restored on entering one */
    u8 unknown_0x1A4[0xE88];
    /* 0x102C */ SM *field_0x102C; /* JT's word: the second state machine of states 9 to 11 */
    u8 unknown_0x1030[0x2F4];
    /* 0x1324 */ ASEG *field_0x1324; /* state 1, at +4 of the run blend at 0x1320 */
    u8 unknown_0x1328[0x4C];
    /* 0x1374 */ ASEG *field_0x1374; /* state 14 when field_0x1878 is 0 */
    u8 unknown_0x1378[0x168];
    /* 0x14E0 */ ASEG *field_0x14E0; /* state 5 */
    u8 unknown_0x14E4[0x120];
    /* 0x1604 */ ASEG *field_0x1604; /* state 7, at +4 of the run blend at 0x1600 */
    u8 unknown_0x1608[0xC8];
    /* 0x16D0 */ LO *field_0x16D0; /* the object it adds, explodes and removes when leaving state 2 */
    /* 0x16D4 */ LO *field_0x16D4; /* the same object when entering state 3 with attach kind 3 or 4 */
    u8 unknown_0x16D8[0x148];
    /* 0x1820 */ ASEG *field_0x1820; /* state 0 when field_0x181C is set */
    u8 unknown_0x1824[0x54];
    /* 0x1878 */ ASEG *field_0x1878; /* state 14 */
};

extern "C" void SetBentleyState(BENTLEY *pbentley, int state)
{
    if (state == pbentley->state)
        return;
    switch (pbentley->state) {
    case 0:
        SetXfKind(pbentley, pbentley->pxfLinear, 2);
        SetXfKind(pbentley, pbentley->pxfAngular, 2);
        ScheduleJtGlance(pbentley);
        break;
    case 9: case 10: case 11:
        SetXfKind(pbentley, pbentley->pxfLinear, 2);
        SetXfKind(pbentley, pbentley->pxfAngular, 2);
        break;
    case 2:
        if (pbentley->field_0x108C == 0) {
            LO *pexpl = 0;
            switch (state) {
            case 0: case 1:
                pexpl = ((BENTLEYSTATEANIMS *)pbentley)->field_0x16D0;
                break;
            case 3:
                switch (pbentley->attachKind) {
                case 1:
                    break;
                case 3: case 4:
                    pexpl = ((BENTLEYSTATEANIMS *)pbentley)->field_0x16D4;
                    break;
                default:
                    pexpl = ((BENTLEYSTATEANIMS *)pbentley)->field_0x16D0;
                    break;
                }
                break;
            }
            if (pexpl != 0) {
                pexpl->Add();
                ExplodeExpl(pexpl);
                pexpl->Remove();
            }
        }
        SetJmpBodyState(pbentley->PvJmp(), -1, 0);
        break;
    case 3:
        SetAttachSubstate(pbentley->PvAttach(), -1);
        break;
    case 4:
        SetJtZapState(pbentley->PvZap(), -1);
        break;
    case 13:
        SetJtPipeState(pbentley->PvPipe(), -1);
        break;
    case 6: {
        GADGETOBJ *pgadget = (GADGETOBJ *)pbentley->ploGadget;
        if (pgadget != 0) {
            pgadget->SetState(1);
            ReleaseBentleyGadget(pbentley);
        }
        SetBentleyGadgetAnim(pbentley, -1);
        break;
    }
    case 8: {
        func_00136530(pbentley, -1);
        pbentley->SetPlayable(1);
        break;
    }
    case 1: case 7: {
        ASEGA *pasega = (ASEGA *)pbentley->field_0x1030;
        ((BENTLEYSTATEANIMS *)pbentley)->field_0x1A0 = pasega->tLocal / pasega->paseg->tLength;
        break;
    }
    case 12:
        CarryThrow_SetState(pbentley->PvCarry(), -1);
        break;
    }
    int stateOld = pbentley->state;
    pbentley->state = state;
    ASEG *pasegNew = 0;
    SM *psm = 0;
    int cAseg = 1;
    int oid = -1;
    int fSm = 4;
    float tLocal = 0.0f;
    float svt = 1.0f;
    void *pfootsteps;
    pbentley->tState = g_2dded0.t;
    switch (state) {
    case 0:
        SetXfKind(pbentley, pbentley->pxfLinear, 1);
        SetXfKind(pbentley, pbentley->pxfAngular, 1);
        if (pbentley->field_0x181C != 0) {
            pasegNew = ((BENTLEYSTATEANIMS *)pbentley)->field_0x1820;
            cAseg = 9;
        } else {
            psm = pbentley->psm;
            oid = stateOld != 2 ? (stateOld != 7 ? 0x175 : 0x176) : 0x178;
            if (IsmsFindSmOptional__FP2SM3OID(psm, oid) < 0)
                oid = -1;
        }
        pbentley->velGoal = g_2a2dd0;
        fSm = func_001430C8(pbentley);
        func_00142868(pbentley, 1);
        break;
    case 1:
        pasegNew = ((BENTLEYSTATEANIMS *)pbentley)->field_0x1324;
        pfootsteps = pbentley->PvBlendState1();
        goto blend;
    case 7:
        pasegNew = ((BENTLEYSTATEANIMS *)pbentley)->field_0x1604;
        pfootsteps = pbentley->PvBlendState7();
    blend:
        cAseg = 9;
        tLocal = ((BENTLEYSTATEANIMS *)pbentley)->field_0x1A0 * pasegNew->tLength;
        ResetRunBlendFootsteps(pfootsteps);
        break;
    case 4:
        SetBinocState(pbentley->PvBinoc(), -1);
        break;
    case 5:
        pasegNew = ((BENTLEYSTATEANIMS *)pbentley)->field_0x14E0;
        cAseg = 9;
        break;
    case 13:
        SetJtPipeState(pbentley->PvPipe(), 0);
        return;
    case 6:
        SetBentleyGadgetAnim(pbentley, 0);
        return;
    case 8:
        func_00136530(pbentley, 0);
        return;
    case 9:
        psm = ((BENTLEYSTATEANIMS *)pbentley)->field_0x102C;
    case 10: case 11:
        SetXfKind(pbentley, pbentley->pxfLinear, 1);
        SetXfKind(pbentley, pbentley->pxfAngular, 1);
        pbentley->velGoal = g_2a2dd0;
        break;
    case 12:
        return;
    case 14:
        pasegNew = ((BENTLEYSTATEANIMS *)pbentley)->field_0x1878;
        if (pasegNew == 0) {
            pasegNew = ((BENTLEYSTATEANIMS *)pbentley)->field_0x1374;
            svt = 1.5f;
        }
        cAseg = 9;
        break;
    }
    RetractAsegaHandle(&pbentley->field_0x1030);
    RetractSmaRef(&pbentley->field_0x1034);
    ApplyAsegToHandle(pasegNew, pbentley, cAseg, &pbentley->field_0x1030, tLocal, svt);
    func_001F14F8(psm, pbentley, oid, cAseg, fSm, &pbentley->field_0x1034);
    pbentley->Slot90();
}
