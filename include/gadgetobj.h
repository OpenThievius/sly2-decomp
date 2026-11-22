/* SPDX-License-Identifier: GPL-3.0-or-later */
/* GADGETOBJ: the object a Bentley gadget leases from its pool (BENTLEYSLOT::ppool, PloLeaseCloneObject): the player keeps it in
   BENTLEY::ploGadget. Its class is not known; slot 76 of its vtable (0x260) is called with 0 or 1 when the gadget is used or
   released. Layout from HandleBentleyMessage, UseBentleyGadget, UseSlyGadget, UpdateBentleyGadget, ReleaseBentleyGadget and FGadgetObjKept;
   JT::pgadgetLeased points at it. C and C++. */
#ifndef SLY2_GADGETOBJ_H
#define SLY2_GADGETOBJ_H
#include "types.h"

struct GADGETOBJVT {
    u8 unknown_0x0[0x260];
    /* 0x260 */ s16 delta;
    /* 0x262 */ s16 index;
    /* 0x264 */ void (*fn)(void *, int);
};

struct GADGETOBJ {
    u8 unknown_0x0[0xC];
    /* 0x00C */ const struct GADGETOBJVT *vt;
    u8 unknown_0x10[0x148];
    /* 0x158 */ s32 field_0x158; /* UpdateBentleyGadget: 2 sticks the object (StickGadgetObj), 4 releases it */
    /* 0x15C */ s32 gadget;      /* the gadget it is for: UseBentleyGadget and HandleBentleyMessage set it from the slot; FGadgetObjKept tests 7 and 0xB */
    u8 unknown_0x160[0xC];
    /* 0x16C */ void *powner;    /* UseBentleyGadget, UseSlyGadget and ReleaseBentleyGadget store the player in it for a kept object */
    u8 unknown_0x170[0x30];
    /* 0x1A0 */ s32 field_0x1A0; /* UpdateBentleyGadget passes it to StickGadgetObj */
};
#endif
