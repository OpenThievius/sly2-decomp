/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GADGETOBJ: the object a Bentley gadget leases from its pool (BENTLEYSLOT::ppool, PloLeaseCloneObject): the player keeps it in
   BENTLEY::ploGadget, JT::pgadgetLeased points at it. Layout from HandleBentleyMessage, UseBentleyGadget, UseSlyGadget,
   UpdateBentleyGadget, ReleaseBentleyGadget, FGadgetObjKept and the gadget object's own functions (src/new_2241d8, src/tn-screen:
   InitGadgetObj, Add/RemoveGadgetObjLoHierarchy, HandleGadgetObjMessage, StickGadgetObj, ReleaseGadgetObj, DetonateGadgetObj).
   In C++ it derives from SO and declares slot 76 (0x260), SetState, as retail's class table shows for class 100 (parent SO 48, size
   0x1B0, whose own new slot is 76: config/recovered/class_diff.tsv; CarryThrow_Launch asks FIsBasicDerivedFrom(obj, 0x64) before
   it calls that slot). That the leased object is of class 100 is a hypothesis from that row. In C the vtable is a plain struct
   (GADGETOBJVT) and LO's flag word at 0x40 is declared by hand. C and C++. */
#ifndef SLY2_GADGETOBJ_H
#define SLY2_GADGETOBJ_H
#include "types.h"
#ifdef __cplusplus
#include "so.h"
#endif

struct SM;
struct SMA;
struct GRFENTRY;

#ifdef __cplusplus
struct GADGETOBJ : SO {
    virtual void SetState(int state);   /* 76: called with 2 (stuck), 3 (released), 5 (a kept one let go), 1 (thrown by CarryThrow_Launch)
                                           and -1 (RemoveGadgetObjLoHierarchy) */
#else
struct GADGETOBJVT {
    u8 unknown_0x0[0x260];
    /* 0x260 */ s16 delta;
    /* 0x262 */ s16 index;
    /* 0x264 */ void (*fn)(void *, int); /* slot 76, SetState */
};

struct GADGETOBJ {
    u8 unknown_0x0[0xC];
    /* 0x00C */ const struct GADGETOBJVT *vt;
    u8 unknown_0x10[0x30];
    /* 0x40: LO::grfSw / LO::pgrfentry (lo.h) */
    union {
        u32 grfSw;
        struct GRFENTRY *pgrfentry;
    };
    u8 unknown_0x44[0x10C];
#endif
    /* 0x150 */ s32 state;       /* the lifecycle state: InitGadgetObj sets -1; FGadgetObjActive (1 to 2), FGadgetObjCanStick and
                                    FIgnoreGadgetObjIntersection (0 and 4), HandleGadgetObjMessage (1 to 2) */
    u8 unknown_0x154[0x4];
    /* 0x158 */ s32 field_0x158; /* UpdateBentleyGadget: 2 sticks the object (StickGadgetObj), 4 releases it; InitGadgetObj sets -1 */
    /* 0x15C */ s32 gadget;      /* the gadget it is for: UseBentleyGadget and HandleBentleyMessage set it from the slot; FGadgetObjKept tests
                                    7 and 0xB; FGadgetObjCanStick, FGadgetObjIsKindB, StickGadgetObj, ReleaseGadgetObj test it */
    u8 unknown_0x160[0x4];
    /* 0x164 */ struct SM *psm;  /* the state machine AddGadgetObjLoHierarchy applies to the object (func_001F1448) when it is set */
    /* 0x168 */ struct SMA *psma; /* the animation that application made: AddGadgetObjLoHierarchy keeps it, RemoveGadgetObjLoHierarchy retracts it */
    /* 0x16C */ void *powner;    /* UseBentleyGadget, UseSlyGadget and ReleaseBentleyGadget store the player in it for a kept object */
    /* 0x170 */ f32 field_0x170; /* InitGadgetObj sets 3000.0 */
    /* 0x174 */ s32 field_0x174; /* DetonateGadgetObj passes it to ExplodeGadgetBurst as its second word */
    /* 0x178 */ s32 field_0x178; /* InitGadgetObj sets -10; DetonateGadgetObj passes it to ExplodeGadgetBurst as its third word */
    u8 unknown_0x17C[0x24];
    /* 0x1A0 */ s32 field_0x1A0; /* UpdateBentleyGadget passes it to StickGadgetObj */
};

#if defined(__mips__)
typedef char check_GADGETOBJ_state[((unsigned int)&((struct GADGETOBJ *)0)->state == 0x150) ? 1 : -1];
typedef char check_GADGETOBJ_psm[((unsigned int)&((struct GADGETOBJ *)0)->psm == 0x164) ? 1 : -1];
typedef char check_GADGETOBJ_powner[((unsigned int)&((struct GADGETOBJ *)0)->powner == 0x16C) ? 1 : -1];
typedef char check_GADGETOBJ_field_0x178[((unsigned int)&((struct GADGETOBJ *)0)->field_0x178 == 0x178) ? 1 : -1];
typedef char check_GADGETOBJ_field_0x1A0[((unsigned int)&((struct GADGETOBJ *)0)->field_0x1A0 == 0x1A0) ? 1 : -1];
#endif
#endif
