#include "dprize.h"
#include "clock.h"
extern "C" {
int PpoolFromLoClone(void *);
SMA *PsmaApplySm(int, void *, int, int);
void RetractSma(void *);
void SetSmaGoal__FP3SMA3OID(void *, int);
void SkipSma(void *, float);
void UnlockLeaseOfPlo(int, void *);
void func_001A58D0(void *, int, int);
extern QW D_002C0D60;
extern QW g_2a2dd0;
}

extern "C" void SetDprizeDprizes(DPRIZE *pdprize, int state)
{
    int sma = -1;
    if (pdprize->dprizes == state)
        return;
    if (state != 0 && state != 5)
        func_001A58D0(pdprize, 0, 0);
    int old = pdprize->dprizes;
    if (old == -1 || old == 2) {
        XF *source = pdprize->pxfLinear;
        pdprize->posSpawn = source->mat.row[3];
        *(QW *)&pdprize->velocity = source->vel;
    }
    {
        switch (state) {
        case 0: {
            int goal = pdprize->smaGoal;
            sma = (~goal != 0) ? goal : 0x184;
            pdprize->field_0x190 = g_2a2dd0;
            break;
        }
        case 3:
        case 4:
            sma = 0x183;
            pdprize->field_0x190 = D_002C0D60;
            break;
        case 2: {
            pdprize->tExpire = 3.4028235e38f;
            pdprize->Remove();
            int pool = PpoolFromLoClone(pdprize);
            if (pool != 0)
                UnlockLeaseOfPlo(pool, pdprize);
            break;
        }
        case 5:
            sma = 0x186;
            pdprize->field_0x190 = g_2a2dd0;
            break;
        }
    }
    switch (state) {
    case 0:
    case 4:
    case 5: {
        LO *child = pdprize->ploShadow;
        if (child != 0)
            child->Add();
        break;
    }
    default: {
        LO *child = pdprize->ploShadow;
        if (child != 0)
            child->Remove();
        break;
    }
    }
    pdprize->dprizes = state;
    pdprize->tDprizes = g_2dded0.t;
    if (sma != -1) {
        SMA *current = pdprize->psma;
        if (current == 0) {
            SMA *created = PsmaApplySm(pdprize->field_0x164, pdprize, sma, 0);
            pdprize->psma = created;
            created->OnAdd();
            float skip = pdprize->dtDelay;
            if (skip > 0.0f)
                SkipSma(pdprize->psma, skip);
        } else {
            SetSmaGoal__FP3SMA3OID(current, sma);
        }
    } else {
        SMA *current = pdprize->psma;
        if (current != 0) {
            RetractSma(current);
            SMA *again = pdprize->psma;
            again->Slot2();
            pdprize->psma = 0;
        }
    }
}
