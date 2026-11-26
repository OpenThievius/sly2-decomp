/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BOMB: the bomb object of the bomb-crusher module, a subclass of SO (include/so.h) with its fields from 0x150 to 0x260; SO slot 60
   is its AddBombCustomXps, slot 16 its update. Fields are read by BOMB's own functions (InitBomb, Bomb_OnPoolClaim, DetonateBomb,
   PrimeBomb, AddBombCustomXps, FIgnoreBombIntersection, InferExpl) and, from 0x210, by the missile family of
   src/bomb-crusher/InitMissile_file.cpp (FireMissile, AddTrigBombOid, AddTrigBombCid, func_001B1F40), whose MISSILE, ROV and TARMISS
   derive from it. It is one class to 0x260 because VECTOR is 16-byte aligned: g++ would size a smaller base up and move a
   subclass's fields. C++ only. */
#ifndef SLY2_BOMB_H
#define SLY2_BOMB_H
#include "so.h"
#include "sly2.h"
#include "asega.h"

/* one custom contact record of BOMB::axp (0x30 bytes): AddBombCustomXps compares the object with the contact's owner */
struct BOMBXP {
    /* 0x00 */ QW pos;
    /* 0x10 */ QW normal;
    /* 0x20 */ f32 dist;
    /* 0x24 */ struct SO *pso; /* the object the contact is with: AddBombCustomXps compares it with the other geometry's owner's OXA owner */
    u8 unknown_0x28[0x8];
};

struct BOMB : SO {
    /* 0x150 */ s32 field_0x150;   /* InitBomb clears it */
    /* 0x154 */ f32 tDetonate;     /* PrimeBomb (min of it and now + dt), Bomb_OnPoolClaim (sets FLT_MAX), InitBomb, DetonateBomb */
    u8 unknown_0x158[0x4];
    /* 0x15C */ f32 radius;        /* the blast radius: GetBombVictims (the bound for most victims), DetonateBomb (sends it in the message to its other bomb as EXPLSO::uPercent), InitBomb sets it */
    /* 0x160 */ f32 radiusJt;      /* the blast radius against a JT (class 0x34): GetBombVictims; InitBomb sets it */
    /* 0x164 */ s32 field_0x164;   /* DetonateBomb: tested against 0 before the victims are collected */
    /* 0x168 */ struct BOMB *pbombOther; /* DetonateBomb sends it message 9 through its slot 51 */
    /* 0x16C */ f32 field_0x16C;   /* DetonateBomb: sent in that message */
    u8 unknown_0x170[0x4];
    /* 0x174 */ s32 field_0x174;   /* Bomb_OnPoolClaim, DetonateBomb clear it */
    u8 unknown_0x178[0x8];
    /* 0x180 */ QW pos180;         /* DetonateBomb: the blast centre (SO slot 29 receives it, victims are measured from it) */
    u8 field_0x190[0x30];          /* DetonateBomb passes its address to SO slot 30 */
    /* 0x1C0 */ QW field_0x1C0;    /* DetonateBomb passes it to SO slot 35 */
    /* 0x1D0 */ QW field_0x1D0;    /* DetonateBomb passes it to SO slot 36 */
    /* 0x1E0 */ s32 field_0x1E0;   /* InitBomb sets 1; DetonateBomb tests it before spawning the hit effect */
    u8 unknown_0x1E4[0x4];
    /* 0x1E8 */ s32 field_0x1E8;   /* Bomb_OnPoolClaim clears it */
    /* 0x1EC */ s32 field_0x1EC;   /* InitBomb sets 0x100; DetonateBomb copies it into each victim message */
    /* 0x1F0 */ s32 field_0x1F0;   /* InitBomb sets -10; DetonateBomb copies it into each victim message */
    /* 0x1F4 */ s32 fCustom;       /* AddBombCustomXps (slot 60): custom contacts present */
    /* 0x1F8 */ s32 cXp;           /* AddBombCustomXps: their count */
    /* 0x1FC */ struct BOMBXP *axp; /* AddBombCustomXps */
    /* 0x200 */ struct BOMB *pbombOwner; /* InitBomb sets it to itself; InferExpl and Bomb_OnPoolClaim; FIgnoreBombIntersection, DetonateBomb read it */
    u8 unknown_0x204[0xC];
    /* 0x210 */ s32 target;      /* FireMissile */
    u8 unknown_0x214[0xC];
    /* 0x220 */ VECTOR posTarget; /* FireMissile */
    /* 0x230 */ void *paseg;     /* FireMissile passes it to ApplyAsegToHandle */
    /* 0x234 */ ASEGA *pasega;   /* the handle ApplyAsegToHandle fills: FireMissile, func_001B1E38 */
    /* 0x238 */ s32 coid;        /* AddTrigBombOid, func_001B1F40: the objects that set it off */
    /* 0x23C */ s32 aoid[4];     /* AddTrigBombOid, func_001B1F40 */
    /* 0x24C */ s32 ccid;        /* AddTrigBombCid, func_001B1F40: the classes that set it off */
    /* 0x250 */ s32 acid[4];     /* AddTrigBombCid, func_001B1F40; func_001B1F40 widens FIgnoreBombIntersection's answer for both */
};

#if defined(__mips__)
SLY2_OFFSET_CHECK(BOMB, tDetonate, 0x154);
SLY2_OFFSET_CHECK(BOMB, pos180, 0x180);
SLY2_OFFSET_CHECK(BOMB, field_0x1C0, 0x1C0);
SLY2_OFFSET_CHECK(BOMB, field_0x1D0, 0x1D0);
SLY2_OFFSET_CHECK(BOMB, axp, 0x1FC);
SLY2_OFFSET_CHECK(BOMB, target, 0x210);
SLY2_OFFSET_CHECK(BOMB, acid, 0x250);
SLY2_SIZE_CHECK(BOMB, 0x260);
#endif
#endif
