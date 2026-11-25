/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SO, the solid object: class 48 of retail's class table, 0x150 bytes, 75 vtable slots, derived from LO (include/lo.h, which
   explains the rules: slot order, names, signatures, which readers a field needs). C++ only. */
#ifndef SLY2_SO_H
#define SLY2_SO_H
#include "lo.h"
#include "dl.h"

struct XF;
struct PHYS;
struct OXA;
struct GEOM;
struct RO;

/* One 0x28-byte entry of SO::field_0xC0 (the object's globs): func_001F5FF8 looks one up by its key, first; func_001F69F8
   (ShowHideLoGlob) and func_001F6A68 set flag 0x800 on one (or all) and bit 50 of its geom's word 0x10 (GEOM::grf). */
struct GLOBENTRY {
    /* 0x0 */ s32 oid;
    u8 unknown_0x4[0x8];
    /* 0xC */ s32 grf;
    u8 unknown_0x10[0x14];
    /* 0x24 */ struct GEOM *pgeom;
};

struct SO : LO {
    virtual void Slot49(int value);     /* 49: func_0010DAF0 passes -1 */
    virtual void GetCpdefi(struct CPDEFI *pcpdefi); /* 50: GetSoCpdefi; GetCmCpdefi, GetJtCpdefi pass the CPDEFI to fill (no override reads $f12) */
    virtual void *PxfFromRef(int id);   /* 51: PxfFromAloRef; CSo_LoadFromBrx passes a shape id and keeps the result */
    virtual void Slot52();
    virtual struct OXA *PoxaAlloc();    /* 53: PoxaAllocSo; RecalcSoLocked keeps the result */
    virtual void Slot54(void *pso);     /* 54: func_001F5988; DiscardSoXps passes another SO or 0 */
    virtual void Slot55();
    virtual void Slot56(void *pxp, int ixpd); /* 56: RecalcSwXpMovement calls it on the object of each side of a contact pair, with the pair and the side's index */
    virtual void Slot57(void *pxp, int ixpd); /* 57: RecalcSwXpMovement, after Slot56 has run on both sides: the same arguments */
    virtual void Slot58();              /* 58: func_001F4F10 */
    virtual void Slot59();
    virtual void Slot60(struct GEOM *pgeom, int cbsp, void *absp, void *pbspLast, void *ptarget); /* 60: func_001F5990; MarkSoCustomContacts */
    virtual int FIgnoreIntersection(struct SO *psoOther); /* 61: FIgnoreSoIntersection; FPoxaPairInteracts */
    virtual int FIsLocked();            /* 62: FIsSoLocked; func_00206380, AddSoGeomToOxa, RemoveSoGeomFromOxa */
    virtual int Slot63();               /* 63: CSo_LoadFromBrx keeps an int (the number of extra records) */
    virtual void Slot64();              /* 64: func_001F3590 */
    virtual void Slot65();
    virtual void Slot66();
    virtual void Slot67();
    virtual void Slot68();
    virtual void Slot69();
    virtual void Slot70();              /* 70: called without arguments (ProjectSoTransform) */
    virtual void Slot71(struct XA *pxa); /* 71: UpdateSoDriven calls it on each XA's water, with the XA */
    virtual void Slot72(void *pwater, float dt); /* 72: AddWaterExternalAccelerations */
    virtual int Slot73(QW pos);         /* 73: UpdateRip */
    virtual void Slot74();              /* 74: func_001F7410; func_001F7950 calls it without arguments */
    virtual int FAbsorbWkr(void *pzpd);  /* 75: FAbsorbSoWkr (SO, a ZPD); ZapTakeDamage passes the object's ZPD */

    /* 0x50 */ s32 cxf;        /* reader: SetSoParent (self and its parent) */
    /* 0x54 */ struct XF *axf; /* readers: SetSoParent (an array of 0x100-byte items: XF's size), func_001F4010 (SO slot 37: multiplies its mat, sets generation) */
    /* 0x58 */ struct XF *pxfLinear;   /* Carry_Attach, ProjectSoTransform, func_001F8F80, func_001CD308 */
    /* 0x5C */ struct XF *pxfAngular;  /* the same functions */
    /* 0x60 */ struct XF *pxfRoot;     /* GetSoCpdefi, func_001F4898, func_001F4930 */
    /* 0x64 */ DL dlChild;             /* InitSo: InitDl(&dlChild, 0x24); func_001CB518, func_001CB5D0, func_001F3CC8 walk it */
    /* 0x70 */ struct LO *ploChildEnd; /* AddSoLoHierarchy (slot 11 of SO) walks dlChild until it meets this */
    u8 unknown_0x74[0xC];
    /* 0x80 */ u8 field_0x80;         /* reader: func_001F3CC8 and CSo_LoadFromBrx pass its address (the globset) */
    u8 unknown_0x81[0x23];
    /* 0xA4 */ s32 cplo;               /* SetAloScrollingMasterSpeeds, func_001F8038, SetAloEyesClosed, func_001F8198 (four readers agree): the object's attached objects */
    /* 0xA8 */ struct LO **aplo;       /* the same four: each entry is tested with FIsBasicDerivedFrom; func_001F8198 compares its oid (0x18) */
    /* 0xAC */ s32 coid;               /* SetAloSelectedOid: the count of aoid */
    /* 0xB0 */ s32 *aoid;              /* SetAloSelectedOid: the oids it looks up */
    /* 0xB4 */ s32 selected;           /* SetAloSelectedOid sets it to 0 or -(index + 3); func_001F8238 clears it (they agree) */
    /* 0xB8 */ s32 field_0xB8;        /* readers: func_001F5FF8 (count), CSo_LoadFromBrx (tested against 0) */
    u8 unknown_0xBC[0x4];
    /* 0xC0 */ struct GLOBENTRY *field_0xC0; /* readers: func_001F5FF8 (array of 0x28-byte entries, key first), func_001F69F8, func_001F6A68 (the same, field_0xB8 many) */
    u8 unknown_0xC4[0x4];
    /* 0xC8 */ s32 field_0xC8;        /* reader: func_001B4478 (an SO's render entry of vtable D_002D4260, whose Init func_001B4438 calls InitSo): it renders the globset through a node stack when it is set */
    /* 0xCC */ s32 islot;              /* func_001CB518 (SO's slot 26) sets it to -1 */
    /* 0xD0 */ u64 field_0xD0;        /* reader: func_001F2768 (sets bit 34 from a flag) */
    u8 unknown_0xD8[0x8];
    /* 0xE0 */ s32 cgeom;              /* ProjectSoTransform, RemoveSoGeomFromOxa (elements of 0xB0 bytes) */
    /* 0xE4 */ struct GEOM *ageom;     /* the same functions, PpartFindAlo, func_001F7A68 (as PART) */
    /* 0xE8 */ struct PHYS *pphys;     /* include/phys.h; FIsSoLocked, ProjectSoTransform, TranslateSoToPos, UpdateSo and others */
    /* 0xEC */ struct OXA *poxa;       /* GetSoNoXpsAll, FFilterSensorSight, RecalcSoLocked and others; func_001F7410 and
                                       func_001F7950 read the same object (+0x6C) as PHYS */
    u8 unknown_0xF0[0x20];
    /* 0x110 */ u8 ainteract[0x1A];    /* GrficFromAlo (reads one byte per take bit), SetAloInteract (writes it): two readers agree */
    u8 unknown_0x12A[0x2];
    /* 0x12C */ f32 uFade;             /* UpdateSo, InitFragile */
    /* 0x130 */ f32 duFade;            /* the same functions */
    /* 0x134 */ struct RO *field_0x134; /* reader: func_001F3CC8 (a 0x30-byte render options block, copied when the caller passes none) */
    /* 0x138 */ struct XA *pxaFirst;   /* the list of XA records driving this object (XA::pxaNextSo): AddSoXa, RemoveSoXa, UpdateSoDriven */
    /* 0x13C */ f32 field_0x13C;       /* InitSo (from a constant) */
    /* 0x140 */ s32 field_0x140;       /* InitSo (-1) */
    u8 unknown_0x144[0x4];
    union {
        /* 0x148 */ u64 grfso;         /* ZapContinue, ExtractUniqueSosFromGeoms, UpdateSwXaList and others */
        s8 bGrfso[8];               /* InitSo stores its first two bytes on their own (sb) */
    };
};

#if defined(__mips__)
SLY2_SIZE_CHECK(SO, 0x150);
SLY2_OFFSET_CHECK(SO, pxfLinear, 0x58);
SLY2_OFFSET_CHECK(SO, pxfAngular, 0x5C);
SLY2_OFFSET_CHECK(SO, pxfRoot, 0x60);
SLY2_OFFSET_CHECK(SO, dlChild, 0x64);
SLY2_OFFSET_CHECK(SO, ploChildEnd, 0x70);
SLY2_OFFSET_CHECK(SO, field_0x13C, 0x13C);
SLY2_OFFSET_CHECK(SO, cxf, 0x50);
SLY2_OFFSET_CHECK(SO, axf, 0x54);
SLY2_OFFSET_CHECK(SO, field_0x80, 0x80);
SLY2_OFFSET_CHECK(SO, field_0xB8, 0xB8);
SLY2_OFFSET_CHECK(SO, field_0xC0, 0xC0);
SLY2_OFFSET_CHECK(SO, field_0xD0, 0xD0);
SLY2_OFFSET_CHECK(SO, field_0x134, 0x134);
SLY2_OFFSET_CHECK(SO, islot, 0xCC);
SLY2_OFFSET_CHECK(SO, cgeom, 0xE0);
SLY2_OFFSET_CHECK(SO, ageom, 0xE4);
SLY2_OFFSET_CHECK(SO, pphys, 0xE8);
SLY2_OFFSET_CHECK(SO, poxa, 0xEC);
SLY2_OFFSET_CHECK(SO, uFade, 0x12C);
SLY2_OFFSET_CHECK(SO, duFade, 0x130);
SLY2_OFFSET_CHECK(SO, grfso, 0x148);
#endif
#endif
