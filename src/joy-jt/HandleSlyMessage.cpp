#include "sly.h"
struct VEC_188F20 {
    float x, y, z, w;
    void Clear() { x = y = z = 0; }
} __attribute__((aligned(16)));
/* the object at SLY::field_0x1034: only its id at 0x30 is read here (one reader, so a view) */
struct OBJ_188F20 { u8 unknown_0x0[0x30]; int id; };
struct ITEM_188F20 { u8 unknown_0x0[0xC]; int grf; u8 unknown_0x10[0x44 - 0x10]; int grfFlags; };
struct MSG9_188F20 { int src; u8 unknown_0x4[4]; int id; };
struct MSG11_188F20 { u8 unknown_0x0[4]; SLY *psly; ITEM_188F20 *pitem; };
extern "C" {
void HandleJtMessage(SLY *, int, void *);
void SetJtJtcs(SLY *, int);
void SetJtState(SLY *, int, int);
void SetJmpState(void *, int, int, int);
void func_00131B10(int, SLY *, int);
void func_00131B60(int, SLY *, int, void *);
QW PosLoWorld(SLY *);
int func_001F1E20(int, QW);
int FIsBasicDerivedFrom(int, int);
int PloFindSwObject_thunk(void *, int, int, SLY *);
void func_001424E0(SLY *, int, int, int);
int func_00205458(int, int);
void GoalAnimLeap_SetState(int, int);
void SpawnSwHitFx(void *, int, QW, SLY *);
void func_0018D698(SLY *, GADGETSLOT *, int);
extern char B_003DD490[];
extern char D_002BF2A0[];
extern char D_002BF2B8[];
}

extern "C" void HandleSlyMessage(SLY *psly, int msg, void *pv)
{
    HandleJtMessage(psly, msg, pv);
    switch (msg) {
    case 3:
        if ((sptr)pv == (sptr)psly->pasegaJtcs) {
            if (psly->jtcs == 10)
                SetJtJtcs(psly, 2);
            else
                SetJtJtcs(psly, -1);
        } else if ((sptr)pv == (sptr)psly->field_0x1030) {
            switch (psly->jts) {
            case 9:
            case 11:
                SetJtState(psly, 0, -1);
                break;
            case 7:
            case 21:
                psly->field_0x1038 = -1;
                break;
            case 5:
                if (psly->field_0x18D0 < 10) {
                    if (psly->field_0x18D0 >= 8)
                        SetJtState(psly, 5, 4);
                }
                break;
            }
        }
        break;
    case 9: {
        MSG9_188F20 *pmsg = (MSG9_188F20 *)pv;
        int src = pmsg->src;
        if (src == (sptr)psly->field_0x1030 || src == (sptr)psly->pasegaJtcs || (psly->field_0x1034 && src == ((OBJ_188F20 *)psly->field_0x1034)->id)) {
            switch (pmsg->id) {
            case 0x16E:
                func_00131B10((sptr)psly->pasegaJtcs, psly, (int)psly->field_0x10B8);
                break;
            case 0x16F:
                func_00131B60((sptr)psly->pasegaJtcs, psly, 3, D_002BF2A0);
                break;
            case 0x170:
                func_00131B60((sptr)psly->pasegaJtcs, psly, 3, D_002BF2B8);
                break;
            case 0x164:
                psly->field_0x18E4 = 1;
                break;
            case 0x166:
                psly->field_0x18E8 = 1;
                break;
            case 0x165:
                if (psly->field_0x18EC) {
                    switch (psly->jtcs) {
                    case 12:
                    case 14:
                    case 16:
                    case 18:
                    case 20:
                        SetJtState(psly, 5, 6);
                        break;
                    case 13:
                    case 15:
                    case 17:
                    case 19:
                    case 21:
                        SetJtState(psly, 5, 7);
                        break;
                    }
                }
                break;
            case 0x167:
                if (psly->field_0x10DC && psly->field_0x1BD4) {
                    int obj = func_001F1E20(psly->field_0x10DC, PosLoWorld(psly));
                    if (obj && !FIsBasicDerivedFrom(obj, 0x5B) && !FIsBasicDerivedFrom(obj, 0x5D)) {
                        int found = PloFindSwObject_thunk(B_003DD490, 1, 0x282, psly);
                        psly->field_0x1BCC = obj;
                        func_001424E0(psly, found, obj, -1);
                    }
                }
                break;
            case 0x173: {
                psly->field_0x1D2C = 1;
                ((VEC_188F20 *)&psly->velGoal)->Clear();
                psly->Slot35(psly->velGoal);
                int leap = func_00205458(psly->field_0x10DC, 0xB1);
                if (leap)
                    GoalAnimLeap_SetState(leap, 4);
                break;
            }
            case 0x174: {
                int leap = func_00205458(psly->field_0x10DC, 0xB1);
                if (leap)
                    GoalAnimLeap_SetState(leap, 6);
                break;
            }
            case 0x16D:
                SpawnSwHitFx(B_003DD490, 0, PosLoWorld(psly), psly);
                break;
            }
        }
        break;
    }
    case 1:
        switch (psly->jts) {
        case 3:
        case 0x16:
            if ((sptr)psly->pjtcsinfo == (sptr)pv)
                SetJmpState(psly->PvJmp(), 0, 0, 0);
            break;
        case 7:
            if (psly->attachKind < 5) {
                if (psly->attachKind >= 3 && (sptr)psly->field_0x4D4 == (sptr)pv)
                    SetJmpState(psly->PvJmp(), 0, 0, 0);
            }
            break;
        }
        {
            GADGETSLOT *pwatch = psly->aslotSly;
            for (int i = 3; i >= 0; i--, pwatch++) {
                if ((sptr)pwatch->plo == (sptr)pv)
                    func_0018D698(psly, pwatch, 0);
            }
        }
        break;
    case 11: {
        MSG11_188F20 *pmsg = (MSG11_188F20 *)pv;
        if (pmsg->psly == psly && (pmsg->pitem->grfFlags & 2)) {
            int grf = pmsg->pitem->grf;
            if (grf & 2) {
                switch (psly->jtcs) {
                case 4:
                case 6:
                case 12:
                case 14:
                case 16:
                case 18:
                case 20:
                    SetJtState(psly, 0, -1);
                    SetJtJtcs(psly, 8);
                    break;
                case 5:
                case 7:
                case 13:
                case 15:
                case 17:
                case 19:
                case 21:
                    SetJtState(psly, 0, -1);
                    SetJtJtcs(psly, 9);
                    break;
                }
            } else if (grf & 4) {
                SetJtState(psly, 0, -1);
                SetJtJtcs(psly, 8);
            }
        }
        break;
    }
    }
}
