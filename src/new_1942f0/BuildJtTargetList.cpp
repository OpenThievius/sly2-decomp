// SPDX-License-Identifier: GPL-3.0-or-later
#include "ps2inline.h"
#include "vu0inline.h"
#include "sw.h"
#include "jt.h"
#include "xfm.h"


/* the target interface of a targetable object: sw.h's TGTDEF (vtable at 0x20, label id at 0x14), the list link follows at 0x24. It is
   pzo_hide.h's MEMBER too (same vtable slots, field 0x14 is -1 without a label), and its DLE is the BYTES8 `kept` that the Attach*
   classes' Clone methods keep after the member. The lists: B_003E13F0 ATTACHCRV (member at 0x190), B_003E13FC ATTACHCYL, B_003E1414
   ATTACHPT (0xE0), B_003E1438 ATTACHZONE (0x130), B_003E1408 ATTACHFLAT (0xE0); the other three are not identified */
struct TARGET : TGTDEF {
    /* 0x24 */ DLE dleTarget;
};

/* the classes before TARGET in each object (the casts retail makes put TARGET at 0x190, 0xE0, 0x130) */
struct BASE190 { u8 unknown_0x0[0x190]; };
struct BASEE0 { u8 unknown_0x0[0xE0]; };
struct BASE130 { u8 unknown_0x0[0x130]; };
struct TGTOBJA : BASE190, TARGET { };
struct TGTOBJB : BASEE0, TARGET { };
struct TGTOBJC : BASE130, TARGET { };
/* the Target class of break-text/InitTarget_file.cpp: an XFM whose own fields start at 0xE0 (the DLE the list B_003E13B4 links it
   through, which CloneTarget keeps across the clone; the flags InitTarget sets to 0x17E) */
struct TGTLOBASE : XFM {
    /* 0xE0 */ DLE dleList;
    /* 0xE8 */ u32 grf;  /* readers: BuildJtTargetList, InitTarget (as the word at 0xE8) */
    u8 unknown_0xEC[0x14];
};
struct TGTLO : TGTLOBASE, TARGET { };

struct HUD;
struct POOLO { u8 unknown_0x0[0x18]; s32 oid; };

extern SW B_003DD490;
extern HUD B_003DA0C0;
extern DL B_003E13B4;
extern DL B_003E13C0;
extern DL B_003E13CC;
extern DL B_003E13D8;
extern DL B_003E13F0;
extern DL B_003E13FC;
extern DL B_003E1408;
extern DL B_003E1414;
extern DL B_003E1438;
extern f32 RO_002BF660;
extern f32 RO_002BF664;
extern f32 RO_002BF70C;

extern "C" {
int FIsPoSwFocusBase(JT *);
void *memset(void *, int, unsigned int);
QW PosLoWorld(JT *);
void InsertTargetCandidate(void *, JT *, QW, void *, TARGET *, int, TGT *);
int FIsBasicDerivedFrom(void *, int);
void EmitTargetSparkles(SW *, JT *, int, TGT *);
void UpdateSwTargetList(SW *, JT *, int, TGT *);
int func_001DA5B0(HUD *);
POOLO *PpoolFromLoClone(LO *);
void ClearHudLabel(HUD *, int);
void ShowHudLabel(float, HUD *, int);
}

static inline int FFarFrom(QW pos, QW posOther)
{
    return RO_002BF660 < LaneX(SqrtX(SquaredLength(VectorSub(pos, posOther))));
}

extern "C" void BuildJtTargetList(void *pv, JT *pjt, int grf)
{
    if (FIsPoSwFocusBase(pjt)) {
        TGT atgt[4];
        QW posJt;
        int ctgt;
        memset(atgt, 0, sizeof(atgt));
        for (unsigned int i = 0; i < 4; i++) {
            atgt[i].iRank = -1;
            atgt[i].sRank = RO_002BF664;
        }
        posJt = PosLoWorld(pjt);
        if (grf & 8) {
            for (TGTOBJA *p = (TGTOBJA *)B_003E13F0.head; p; p = (TGTOBJA *)p->dleTarget.next)
                InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        if (grf & 0x10) {
            for (TGTOBJB *p = (TGTOBJB *)B_003E13FC.head; p; p = (TGTOBJB *)p->dleTarget.next)
                InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        if (grf & 0x80) {
            for (TGTOBJB *p = (TGTOBJB *)B_003E1414.head; p; p = (TGTOBJB *)p->dleTarget.next)
                InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        if (grf & 4) {
            for (TGTOBJC *p = (TGTOBJC *)B_003E1438.head; p; p = (TGTOBJC *)p->dleTarget.next)
                InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        if (grf & 0x400) {
            for (TGTOBJB *p = (TGTOBJB *)B_003E13D8.head; p; p = (TGTOBJB *)p->dleTarget.next)
                InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        if (grf & 0x200) {
            for (TGTOBJA *p = (TGTOBJA *)B_003E13CC.head; p; p = (TGTOBJA *)p->dleTarget.next)
                InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        if (grf & 2) {
            for (TGTOBJA *p = (TGTOBJA *)B_003E13C0.head; p; p = (TGTOBJA *)p->dleTarget.next)
                InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        if (grf & 1) {
            for (TGTLO *p = (TGTLO *)B_003E13B4.head; p; p = (TGTLO *)p->dleList.next)
                if ((p->grf & 1) && FIsBasicDerivedFrom(p, 0x13))
                    InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        if (grf & 0x20) {
            for (TGTOBJB *p = (TGTOBJB *)B_003E1408.head; p; p = (TGTOBJB *)p->dleTarget.next)
                InsertTargetCandidate(pv, pjt, posJt, p, p, 4, atgt);
        }
        for (ctgt = 4; ctgt > 0 && atgt[ctgt - 1].oid == 0; ctgt--)
            ;
        EmitTargetSparkles(&B_003DD490, pjt, ctgt, atgt);
        UpdateSwTargetList(&B_003DD490, pjt, ctgt, atgt);
        int idCur = func_001DA5B0(&B_003DA0C0);
        if (idCur == -1 || idCur == B_003DD490.field_0x4740) {
            int idLabel;
            if (B_003DD490.ctgt == 0 || FFarFrom(posJt, B_003DD490.atgt[0].pos)) {
                idLabel = -1;
            } else {
                POOLO *ppool = 0;
                if (B_003DD490.atgt[0].ploClone)
                    ppool = PpoolFromLoClone(B_003DD490.atgt[0].ploClone);
                if (ppool && ppool->oid == 0x624 && RO_002BF70C < B_003DD490.atgt[0].tShown)
                    idLabel = 0x125;
                else
                    idLabel = B_003DD490.atgt[0].ptgtdef->idLabel;
            }
            if (idLabel != idCur) {
                if (idLabel == -1)
                    ClearHudLabel(&B_003DA0C0, B_003DD490.field_0x4740);
                else
                    ShowHudLabel(-1.0f, &B_003DA0C0, idLabel);
                B_003DD490.field_0x4740 = idLabel;
            }
        }
    }
}
