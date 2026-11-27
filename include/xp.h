/* SPDX-License-Identifier: GPL-3.0-or-later */
/* XP, the contact record between two objects, and XPD, one side of it. Names and meanings are ours, from what retail's code does with them.
   An XP is 0xC0 bytes: Sw_Construct creates SW::slotheapMq with 0xC0-byte slots, PxpAdd allocates one there and fills it, CloneMqList
   copies one whole (0xC0, quadword-aligned) and FreeSwMqList returns a chain to the same heap. The lists are linked through pxpNext.
   Every function that takes one (the AdjustNewXp methods, slot 55 of SO: PxpAdd calls it with the record and the side index) indexes the
   two sides with `side << 6`, so XPD is 0x40 bytes. Each source used to declare its own view (MQ, SIDE, XPSIDE, XPD, HALF, MQSIDE).
   The class is certain (PxpAdd builds it), so one reader is enough for a field (include/lo.h's rule); the readers are listed. C++ only. */
#ifndef SLY2_XP_H
#define SLY2_XP_H
#include "types.h"
#include "sly2.h"

struct GEOM;
struct XF;
struct SO;

/* One side of a contact (0x40 bytes): the shape that touched, its transform and objects, and where it touched. */
struct XPD {
    /* 0x00 */ struct GEOM *pgeom; /* PxpAdd (its object argument), AdjustBentleyNewXp (grf), MarkSoCustomContacts, func_001F7410 (grftak),
                                      ClipLaserBeams (the weapon record's part) */
    /* 0x04 */ struct XF *pxf;     /* PxpAdd (GEOM::pxf, passed to ConvertXfPos), RecalcSwXpMovement (VelocityXfAtPos) */
    /* 0x08 */ struct SO *psoRoot; /* PxpAdd (pgeom->pso->poxa->owner: the root of the object's contact record); UpdateButton and func_001F7410
                                      compare it with the OXA owner, NotifyLaserXpEnded and AdjustStepXps with the object itself; AdjustLootNewXp,
                                      AdjustVehicleNewXp, Chaser_AdjustNewXp read the other side's */
    /* 0x0C */ struct SO *pso;     /* PxpAdd (GEOM::pso, the shape's object, called through slot 55), RecalcSwXpMovement (slots 56, 57),
                                      MarkSoCustomContacts, AdjustMurrayNewXp (FIsLocked), UpdateButton, ClipLaserBeams, func_001F7410 */
    /* 0x10 */ QW pos;             /* PxpAdd, RecalcSwXpMovement, ClipLaserBeams, AdjustStepXps, func_001F7410 */
    /* 0x20 */ QW posConv;         /* PxpAdd: pos through ConvertXfPos */
    /* 0x30 */ QW vel;             /* RecalcSwXpMovement (VelocityXfAtPos), func_001F7410 (the weapon record's velocity) */
};

struct XP {
    /* 0x00 */ XPD axpd[2];
    union {
        /* 0x80 */ QW normal;      /* PxpAdd (its vel argument: AddBombCustomXps passes its normal), AdjustVehicleNewXp */
        /* 0x80 */ VECTOR vecNormal; /* the same: AdjustMurrayNewXp and AdjustSlyNewXp read its z */
    };
    /* 0x90 */ f32 gScale;         /* PxpAdd (its float argument), AdjustStepXps (smallest of kind 0xE), func_001D2DD0 (largest) */
    /* 0x94 */ f32 friction;       /* PxpAdd (a constant), AdjustVehicleNewXp, AdjustSlyNewXp, AdjustJtZapNewXp (ZAPXP) */
    /* 0x98 */ f32 bounce;         /* PxpAdd (a constant), AdjustVehicleNewXp, AdjustSlyNewXp, AdjustJtZapNewXp (ZAPXP) */
    /* 0x9C */ s32 kind;           /* PxpAdd (its argument), AdjustStepXps (0xE), func_001F90D0 (0xD, 0xE), UpdateButton (10), AdjustSlyNewXp (0xE) */
    union {
        /* 0xA0 */ s32 nUser;      /* PxpAdd stores its argument from a general register: an address from RecalcSwXpAll's callers, the
                                      laser's distance as float bits */
        /* 0xA0 */ f32 s;          /* ClipLaserBeams reads it as a float (the distance along the beam) */
    };
    /* 0xA4 */ s32 field_0xA4;     /* PxpAdd stores its last register argument */
    /* 0xA8 */ s32 ixp;            /* func_001F90D0: the record's index in its array */
    /* 0xAC */ XP *pxpNext;        /* PxpAdd, FreeSwMqList, CloneMqList, PrependMqList, AdjustStepXps, UpdateButton, func_001F90D0 */
    /* 0xB0 */ QW velRel;          /* RecalcSwXpMovement: the first side's velocity less the second's */
};

#if defined(__mips__)
typedef char check_XPD_size[(sizeof(XPD) == 0x40) ? 1 : -1];
typedef char check_XP_kind[((unsigned int)&((XP *)0)->kind == 0x9C) ? 1 : -1];
typedef char check_XP_pxpNext[((unsigned int)&((XP *)0)->pxpNext == 0xAC) ? 1 : -1];
typedef char check_XP_size[(sizeof(XP) == 0xC0) ? 1 : -1];
#endif
#endif
