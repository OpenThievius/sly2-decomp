/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BASIC and LO, the roots of the game's object classes (docs/ROADMAP.md "Next", item 1).

   Retail's class table (0x2BAAE8, config/recovered/class_diff.tsv) gives each class its parent, size and vtable: class 0
   (0x10 bytes) is the root, class 2 (0x50 bytes, 48 slots) is LO. g++ 2.95 puts the vtable pointer after the own fields of
   the first class that declares a virtual, and retail reads it at 0xC: so BASIC has 0xC bytes of fields and declares the
   first virtuals. Class 155, the other branch from the root, shares slots 1, 2, 4 and 5 with LO and overrides 3 and 6, so
   slots 1 to 6 are BASIC's. A vtable entry is 8 bytes (delta, index, function); slot n sits at 8 * n, after the type-info
   entry, so the virtuals are declared here in slot order and their order must not change.

   A virtual is named after the function retail puts in its slot (the base class's, then the first override with a name),
   without the class in the name; Slot<n> where none has a name yet. A signature is written only where a matched caller
   shows it; the others are `void ()` placeholders.

   A field is here when a matched function reads it at that offset, and no matched function reads the offset as another type.
   One reader is enough when it is a method of the class (its vtable holds it) or the class is otherwise certain; two are
   needed when the class of the object is only a guess from a local struct's name. The readers are listed. C++ only. */
#ifndef SLY2_LO_H
#define SLY2_LO_H
#ifndef __cplusplus
#error "lo.h declares C++ classes"
#endif
#include "types.h"

struct SO;
struct CLASSINFO;
struct RO;
struct SCOPE;
struct GRFENTRY;
struct CFrame;

struct BASIC {
    /* 0x0 */ struct CFrame *pframe;    /* the object's frame pointer (a CFramePtr): ApplyAseg copies it from the ASEG to its ASEGA
                                          (CFramePtr_Assign), Asega_Release clears it, PostLoLoad (LO slot 15) asks it for binding 1 */
    /* 0x4 */ struct CSidebag *psidebag; /* reader: RefGetOption (0x200BA0) calls its FFindBinding; RefSetOption, RefAddOption and
                                            RefEnsureOption (retail names P5BASIC) pass it to the CSidebag binding functions */
    /* 0x8 */ struct SUBSCRIBER *psubFirst; /* the objects subscribed to this one, a list of SUBSCRIBER (defined where used): SubscribeLoObject, UnsubscribeLoObject, Basic_FreeSubscribers (three readers, one per function of OnLoAdd_file.cpp) */
    /* 0xC: the vtable pointer */
    virtual void OnAdd();               /*  1: OnLoAdd */
    virtual void Slot2();               /*  2: func_00132B08 */
    virtual void HandleSpliceEvent(int event, int argument0, int argument1, int argument2, int argument3); /*  3: HandleLoSpliceEvent (LO); SetHbskHbsks passes five words */
    virtual void PostMessage(int msgid, void *pv); /*  4: PostLoMessage (LO *, int, void *); UpdateWater passes a message id and its data */
    virtual void HandleMessage(int msgid, void *pv);       /*  5: HandleLoMessage; ReleaseRip passes 8 and the RIP */
    virtual struct CLASSINFO *Slot6();  /*  6: func_00113A30 (LO), func_00113D10 (SO); PeopidFind returns its result (cid at +4) */
};

/* A search scope, 0x28 bytes: AllocSwBuffers allocates the world's default (SW::pscopeDefault) at that size, sets words 0x0 and
   0x8 to -1 and initialises a list at 0x18; an LO points at its own (LO::pscope), which PloFindSwObject takes in its place. */
struct SCOPE {
    /* 0x0 */ s32 field_0x0;           /* AllocSwBuffers sets it to -1 on the world's default scope */
    /* 0x4 */ struct SCOPE *pscopeParent; /* the clone path's parent scope: func_001A6260, FLoHasOid (walk it), CLo_Clone, PcnodeFindOrAddClonePath (its CNODE) */
    /* 0x8 */ s32 field_0x8;           /* AllocSwBuffers sets it to -1; FLoHasOid compares it with an object id */
    u8 unknown_0xC[0x4];
    /* 0x10 */ struct LO *plo;         /* the object the scope belongs to: func_001A6260, FLoHasOid, CLo_Clone (all stop when it differs) */
    u8 unknown_0x14[0x4];
    /* 0x18 */ u8 sl[0xC];             /* a list (sl.h's SL, not included here: several sources declare their own) that
                                          AllocSwBuffers starts with InitSl (item size 0x14) */
    /* 0x24 */ s32 field_0x24;         /* InitCloneSets sets it to 1 on each clone's scope */
};

struct LO : BASIC {
    virtual void Init();                /*  7: InitLo, InitSo */
    virtual void Add();                 /*  8: AddLo; InstantiateClone calls it without arguments */
    virtual void Remove();              /*  9: RemoveLo; called without arguments (UpdateSo, InitFragile) */
    virtual void SetParent(struct LO *ploParent, void *pv, int grf); /* 10: SetLoParent, SetSoParent; func_001CD308 and
                                           Carry_Attach pass a pointer second */
    virtual void AddHierarchy();        /* 11: AddLoHierarchy, AddSoLoHierarchy */
    virtual void RemoveHierarchy();     /* 12: RemoveLoHierarchy */
    virtual void Slot13(struct LO *plo, struct SO *psoOldParent); /* 13: func_001A5B80; SetLoParent passes the object and its old parent */
    virtual void LoadFromBrx();         /* 14: LoadLoFromBrx, CSo_LoadFromBrx */
    virtual void PostLoad();            /* 15: PostLoLoad, PostSoLoad */
    virtual void Update();              /* 16: UpdateLo, UpdateSo */
    virtual void ProjectTransform();    /* 17: func_001A5E80, ProjectSoTransform */
    virtual void UpdateXfWorldHierarchy(); /* 18: func_0022FBD8, UpdateAloXfWorldHierarchy; called without arguments (TranslateSoToPos) */
    virtual void Slot19();
    virtual void Slot20(void *pcm, float uAlpha, float uAlphaOther, struct RO *pro); /* 20: called on each child by func_001F3CC8 (render) */
    virtual void Slot21(int arg); /* 21: called by func_001B81B8 on the carried object, with 0 (take) or 1 (let go) */
    virtual void RemoveAloHierarchy();  /* 22: RemoveAloHierarchy */
    virtual void Slot23();
    virtual void Slot24();
    virtual void SetCloneId(u32 cloneid, int grf); /* 25: LO_SetCloneId, ALO_SetCloneId (SO); InstantiateClone and
                                           InitCloneSets pass MakeCloneId's result and 1 */
    virtual void Slot26(void *pv);      /* 26: func_001CB4E0, func_001CB518 (SO); func_001CB518 calls it on each child */
    virtual void Slot27(void *pv);      /* 27: func_001CB5C8, func_001CB5D0 (SO); func_001CB5D0 calls it on each child */
    virtual int CReturnZero(struct LO ***papalo); /* 28: CReturnZeroLo returns 0 (no children); AddLo, RemoveLo and SetLoParent pass the
                                           address of a child array pointer and loop over the returned count */
    virtual void TranslateToPos(QW pos); /* 29: TranslateSoToPos (SO); func_001B0D90 passes a quadword */
    virtual void Slot30(void *pv);
    virtual struct MATRIX4 *PmatWorld(); /* 31: LO_PmatWorld, PmatWorldSo; Carry_Attach copies four quadwords from it */
    virtual void *Slot32(void *pmat);   /* 32: func_001A6B30, func_001F3FB0; func_001CD308 passes a matrix buffer, keeps the result as an XF */
    virtual QW GetVelocityVec();        /* 33: GetSoVelocityVec (SO); MatchSoOtherObject, func_001F7950 keep the quadword */
    virtual QW Slot34();                /* 34: MatchSoOtherObject */
    virtual void Slot35(QW vec);        /* 35: MatchSoOtherObject passes slot 33's result */
    virtual void Slot36(QW vec);        /* 36: MatchSoOtherObject passes slot 34's result */
    virtual void Slot37(void *pmat);    /* 37: func_001A6450, func_001F4010 (SO); InstantiateClone passes the clone's matrix */
    virtual void SetPosMatFromLo(struct LO *plo);     /* 38: SetLoPosMatFromLo */
    virtual void SetPosMatFromXf();     /* 39: SetLoPosMatFromXf */
    virtual void CloneVirtual(struct LO *ploSource); /* 40: CloneLoVirtual; PloCloneLo passes the object it clones (signature from that caller) */
    virtual void Slot41(struct SO *psoSource); /* 41: CloneAloHierarchy passes the source object (an SO) */
    virtual void Slot42(float value);   /* 42: func_001F3118 (SO) stores it in field_0x38 and passes it to each child's slot 42 */
    virtual unsigned FReturnFalse(int ipart); /* 43: FReturnFalseLo; func_00130010 passes a part index and keeps the unsigned the ALO override returns */
    virtual void Slot44(int ipart);     /* 44: ApplyAseg calls it on each part's object with the part index */
    virtual void Slot45(int ipart);     /* 45: RetractAsega calls it on each part link's object with the part index (the same word ApplyAseg passed to slot 44) */
    virtual void Slot46(int grf);       /* 46: SetLoGrfzon passes its grf (the zone bits it then ors into each parent) */
    virtual void SetGrfField(u32 grf);  /* 47: SetLoGrfField; func_001F2FE0 passes a mask to each child */
    virtual void ClearGrfField(u32 grf); /* 48: ClearLoGrfField; func_001F3078 passes a mask to each child */

    /* 0x10 */ struct SO *psoParent;   /* InitSo, FFilterSensorSight (followed up to the root) */
    /* 0x14 */ s32 proot;              /* FFilterSensorSight (compared as an id), PoxaAllocSw (a list entry) */
    /* 0x18 */ s32 oid; /* the object id: FLoHasOid, PostMurrayLoad (Murray slot 15) and others */
    u8 unknown_0x1C[0x4];
    /* 0x20 */ struct LO *ploNextCid;  /* the next object of the same class id: the link of SW::aslCid's lists (Sw_Construct's InitSl
                                       ibSle 0x20); func_002102A0 walks them */
    /* 0x24 */ struct LO *ploNext;     /* the next child of the same parent: func_001CB518, func_001CB5D0, func_001F3CC8. The parent's
                                       list has ibDle 0x24 (InitSo), but this is not declared as a DLE: its prev would be 0x28,
                                       and retail reads grfo there as 64 bits (ld 0x28 in RecalcSoLocked, func_001C4BD8) */
    /* 0x28 */ u64 grfo;               /* RecalcSoLocked, func_001C4BD8, UpdateRip */
    /* 0x30 */ f32 tUpdate;            /* UpdateLo (slot 16) runs HandleSpliceEvent 1 once the clock has passed it */
    /* 0x34 */ struct DCB *pdcb;       /* the object's callback table (PdcbAllocSw's result): func_001A5D98 runs its pfn(plo, pv). DCB is declared by its users */
    /* 0x38 */ f32 field_0x38;         /* func_001F3118 (SO slot 42): set to its argument, compared with each child's */
    /* 0x3C */ struct SCOPE *pscope;   /* what PloFindSwObject searches when this object is the context: RefOpFindObject,
                                       func_001241E8, func_00124578, RefOpFindNearestObject; InitCloneSets sets its 0x24 */
    /* 0x40: flags until AddSwGrfEntry enters the object in the world's table (include/sw.h), then its entry, which keeps the
       flags; AddSwGrfEntry tests bit 0x40 first and repoints it when it compacts the table. SolveSw and func_001CDA80 call
       LO slots on the entries' objects, so the object is an LO. */
    union {
        u32 grfSw;
        struct GRFENTRY *pgrfentry;
    };
    u8 unknown_0x44[0xC];
};

/* Retail's layout, checked by the PS2 build: a field or a size that moves fails to compile. */
#if defined(__mips__)
#define SLY2_OFFSET_CHECK(type, field, offset) \
    typedef char check_##type##_##field[((unsigned int)&((type *)0)->field == (offset)) ? 1 : -1]
#define SLY2_SIZE_CHECK(type, size) typedef char check_##type##_size[(sizeof(type) == (size)) ? 1 : -1]
SLY2_SIZE_CHECK(BASIC, 0x10);
SLY2_SIZE_CHECK(LO, 0x50);
SLY2_OFFSET_CHECK(BASIC, pframe, 0x0);
SLY2_OFFSET_CHECK(BASIC, psidebag, 0x4);
SLY2_OFFSET_CHECK(BASIC, psubFirst, 0x8);
SLY2_OFFSET_CHECK(LO, psoParent, 0x10);
SLY2_OFFSET_CHECK(LO, proot, 0x14);
SLY2_OFFSET_CHECK(LO, pdcb, 0x34);
SLY2_OFFSET_CHECK(LO, oid, 0x18);
SLY2_OFFSET_CHECK(LO, ploNextCid, 0x20);
SLY2_OFFSET_CHECK(LO, ploNext, 0x24);
SLY2_OFFSET_CHECK(LO, tUpdate, 0x30);
SLY2_OFFSET_CHECK(LO, grfo, 0x28);
SLY2_OFFSET_CHECK(LO, pscope, 0x3C);
SLY2_OFFSET_CHECK(LO, pgrfentry, 0x40);
SLY2_SIZE_CHECK(SCOPE, 0x28);
SLY2_OFFSET_CHECK(SCOPE, sl, 0x18);
#endif
#endif
