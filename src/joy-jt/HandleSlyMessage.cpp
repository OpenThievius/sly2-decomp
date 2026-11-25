#include "types.h"
#include "lo.h"
struct VEC_188F20 {
    float x, y, z, w;
    void Clear() { x = y = z = 0; }
} __attribute__((aligned(16)));
struct SLY_188F20;
struct OBJ_188F20 { u8 unknown_0x0[0x30]; int id; };
struct WATCH_188F20 { u8 unknown_0x0[8]; int target; };
struct ITEM_188F20 { u8 unknown_0x0[0xC]; int grf; u8 unknown_0x10[0x44 - 0x10]; int grfFlags; };
struct MSG9_188F20 { int src; u8 unknown_0x4[4]; int id; };
struct MSG11_188F20 { u8 unknown_0x0[4]; SLY_188F20 *psly; ITEM_188F20 *pitem; };
struct SLY_188F20 : LO {
    u8 unknown_0x50[0x190 - 0x50];
    VEC_188F20 v;
    u8 unknown_0x1A0[0x2C0 - 0x1A0];
    char jmp[0x4C8 - 0x2C0];
    int attachState;
    u8 unknown_0x4CC[0x4D4 - 0x4CC];
    int attachTarget;
    u8 unknown_0x4D8[0x1030 - 0x4D8];
    int id1030;
    OBJ_188F20 *pobj1034;
    int n1038;
    u8 unknown_0x103C[0x10B8 - 0x103C];
    int n10B8;
    u8 unknown_0x10BC[0x10DC - 0x10BC];
    int n10DC;
    u8 unknown_0x10E0[0x18C4 - 0x10E0];
    int n18C4;
    int state;
    u8 unknown_0x18CC[0x18D0 - 0x18CC];
    int n18D0;
    u8 unknown_0x18D4[0x18D8 - 0x18D4];
    int jtcs;
    u8 unknown_0x18DC[0x18E0 - 0x18DC];
    int id18E0;
    int f18E4;
    int f18E8;
    int f18EC;
    u8 unknown_0x18F0[0x1BCC - 0x18F0];
    int obj1BCC;
    u8 unknown_0x1BD0[0x1BD4 - 0x1BD0];
    int f1BD4;
    u8 unknown_0x1BD8[0x1D2C - 0x1BD8];
    int f1D2C;
    u8 unknown_0x1D30[0x1FB0 - 0x1D30];
    WATCH_188F20 awatch[4];
};
extern "C" {
void HandleJtMessage(SLY_188F20 *, int, void *);
void SetJtJtcs(SLY_188F20 *, int);
void SetJtState(SLY_188F20 *, int, int);
void SetJmpState(void *, int, int, int);
void func_00131B10(int, SLY_188F20 *, int);
void func_00131B60(int, SLY_188F20 *, int, void *);
QW PosLoWorld(SLY_188F20 *);
int func_001F1E20(int, QW);
int FIsBasicDerivedFrom(int, int);
int PloFindSwObject_thunk(void *, int, int, SLY_188F20 *);
void func_001424E0(SLY_188F20 *, int, int, int);
int func_00205458(int, int);
void GoalAnimLeap_SetState(int, int);
void SpawnSwHitFx(void *, int, QW, SLY_188F20 *);
void func_0018D698(SLY_188F20 *, WATCH_188F20 *, int);
extern char B_003DD490[];
extern char D_002BF2A0[];
extern char D_002BF2B8[];
}

extern "C" void HandleSlyMessage(SLY_188F20 *psly, int msg, void *pv)
{
    HandleJtMessage(psly, msg, pv);
    switch (msg) {
    case 3:
        if ((sptr)pv == psly->id18E0) {
            if (psly->jtcs == 10)
                SetJtJtcs(psly, 2);
            else
                SetJtJtcs(psly, -1);
        } else if ((sptr)pv == psly->id1030) {
            switch (psly->state) {
            case 9:
            case 11:
                SetJtState(psly, 0, -1);
                break;
            case 7:
            case 21:
                psly->n1038 = -1;
                break;
            case 5:
                if (psly->n18D0 < 10) {
                    if (psly->n18D0 >= 8)
                        SetJtState(psly, 5, 4);
                }
                break;
            }
        }
        break;
    case 9: {
        MSG9_188F20 *pmsg = (MSG9_188F20 *)pv;
        int src = pmsg->src;
        if (src == psly->id1030 || src == psly->id18E0 || (psly->pobj1034 && src == psly->pobj1034->id)) {
            switch (pmsg->id) {
            case 0x16E:
                func_00131B10(psly->id18E0, psly, psly->n10B8);
                break;
            case 0x16F:
                func_00131B60(psly->id18E0, psly, 3, D_002BF2A0);
                break;
            case 0x170:
                func_00131B60(psly->id18E0, psly, 3, D_002BF2B8);
                break;
            case 0x164:
                psly->f18E4 = 1;
                break;
            case 0x166:
                psly->f18E8 = 1;
                break;
            case 0x165:
                if (psly->f18EC) {
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
                if (psly->n10DC && psly->f1BD4) {
                    int obj = func_001F1E20(psly->n10DC, PosLoWorld(psly));
                    if (obj && !FIsBasicDerivedFrom(obj, 0x5B) && !FIsBasicDerivedFrom(obj, 0x5D)) {
                        int found = PloFindSwObject_thunk(B_003DD490, 1, 0x282, psly);
                        psly->obj1BCC = obj;
                        func_001424E0(psly, found, obj, -1);
                    }
                }
                break;
            case 0x173: {
                psly->f1D2C = 1;
                psly->v.Clear();
                psly->Slot35(*(QW *)&psly->v);
                int leap = func_00205458(psly->n10DC, 0xB1);
                if (leap)
                    GoalAnimLeap_SetState(leap, 4);
                break;
            }
            case 0x174: {
                int leap = func_00205458(psly->n10DC, 0xB1);
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
        switch (psly->state) {
        case 3:
        case 0x16:
            if (psly->n18C4 == (sptr)pv)
                SetJmpState(psly->jmp, 0, 0, 0);
            break;
        case 7:
            if (psly->attachState < 5) {
                if (psly->attachState >= 3 && psly->attachTarget == (sptr)pv)
                    SetJmpState(psly->jmp, 0, 0, 0);
            }
            break;
        }
        {
            WATCH_188F20 *pwatch = psly->awatch;
            for (int i = 3; i >= 0; i--, pwatch++) {
                if (pwatch->target == (sptr)pv)
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
