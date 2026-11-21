// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "sw.h"

struct ENT { int kind; int arg; };
struct NODE { int id; int fForward; int count; ENT *ents; };
struct STGSWITCH : LO {
    u8 unknown_0x50[0x108];
    /* 0x158 */ int flag;
    u8 unknown_0x15C[0xC];
    /* 0x168 */ int grfFx;
};

/* An explosion's parameters, 0x40 bytes: the layout ExplodeExplParams fills (src/dzg-emitter/InitEmitb_file.cpp). */
struct EXPLP {
    u32 grfexpl;
    LO *palo;
    f32 r1;
    f32 r2;
    QW pos;
    QW normal;
    QW unknown_0x30;
};

/* Class 0x1E (an explosion): slot 51 explodes it with EXPLP, as ExplodeExpl and ExplodeExplParams call it. */
struct EXPL : LO {
    virtual void Slot49();
    virtual void Slot50();
    virtual void Explode(EXPLP *pexplp);
};

extern "C" {
LO *PloFindSwObject_thunk(SW *, int, int, void *);
void func_001F6978(STGSWITCH *, int);
void func_001F69F8(STGSWITCH *, int);
void func_001F6AC8(STGSWITCH *, int);
void func_001F6B48(STGSWITCH *, int);
int FIsBasicDerivedFrom(LO *, int);
void JoltCm(void *, int);
void TriggerJoyRumbleRumk__FP3JOY4RUMKf(void *, int, float);
QW PosLoWorld(LO *);
void OnDifficultyBreak(void *, QW, int, int, void *);
void ApplyTaskStateRequests(void *, int, int, void *);
extern SW B_003DD490;
extern char B_002DDF40[];
extern char B_002DFC00[];
extern char B_002DE578[];
extern char B_002DEB30[];

void RunStgSwitchStage(STGSWITCH *psw, NODE *pnode)
{
    LO *ploLast = 0;
    for (int index = 0; index < pnode->count; index++) {
        ENT *ent = &pnode->ents[index];
        if ((psw->flag > 0 || pnode->fForward <= 0) && ((0x3F >> ent->kind) & 1))
            continue;
        LO *plo = 0;
        if ((0xC3 >> ent->kind) & 1) {
            plo = PloFindSwObject_thunk(&B_003DD490, 1, ent->arg, psw);
            if (plo == 0)
                continue;
        }
        switch (ent->kind) {
        case 6:
            ploLast = plo;
            break;
        case 0: plo->Add(); break;
        case 1: plo->Remove(); break;
        case 2: func_001F6978(psw, ent->arg); break;
        case 3: func_001F69F8(psw, ent->arg); break;
        case 4: func_001F6AC8(psw, ent->arg); break;
        case 5: func_001F6B48(psw, ent->arg); break;
        case 7:
            if (FIsBasicDerivedFrom(plo, 0x1E)) {
                EXPLP explp;
                explp.grfexpl = 1;
                explp.palo = ploLast ? ploLast : plo;
                ((EXPL *)plo)->Explode(&explp);
            }
            break;
        case 8:
            if (psw->grfFx & 2)
                JoltCm(B_002DDF40, ent->arg);
            break;
        case 9:
            if (psw->grfFx & 4)
                TriggerJoyRumbleRumk__FP3JOY4RUMKf(B_002DFC00, ent->arg, 0.3f);
            break;
        case 10:
            if (psw->grfFx & 8) {
                QW pos;
                if (ploLast)
                    pos = PosLoWorld(ploLast);
                else
                    pos = PosLoWorld(psw);
                OnDifficultyBreak(B_002DE578, pos, ent->arg, -100, psw);
            }
            break;
        case 11: {
            void *apv[1];
            apv[0] = &ent->arg;
            psw->HandleSpliceEvent(4, 0, 1, (sptr)apv, 0);
            break;
        }
        case 12:
            ApplyTaskStateRequests(B_002DEB30, 1, ent->arg, psw);
            break;
        }
    }
}
}
