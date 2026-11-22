/* SPDX-License-Identifier: GPL-3.0-or-later */
/* PO, a playable object: class 50 of retail's class table (0x2BAAE8), 0x180 bytes, derived from SO (include/so.h). Its vtable
   adds slots 76 to 81 and holds InitPo (7), HandlePoMessage (5), LoadPoFromBrx (14), ClonePo (41). The name follows those
   functions (source: their recovered names) and Sly 1's PO (sly1 include/po.h, CC0). A field is read by a function certain to hold
   a PO (or a class derived from it). C++ only. */
#ifndef SLY2_PO_H
#define SLY2_PO_H
#include "so.h"

struct JOY;
struct TN;
struct MAGNET {
    u8 unknown_0x0[0xC];
};

struct PO : SO {
    virtual int FInvulnerable(int grf); /* 76: FInvulnerablePo, FInvulnerableJt, FInvulnerableBentley, FInvulnerableMurray; UpdateGuardDamage passes the damage's flags */
    virtual int NAlertLevel();          /* 77: func_001C3ED0 (PO), NGuardAlertLevel (STEPGUARD); NNextSensorState reads it */
    virtual void OnActive(int fActive); /* 78: OnPoActive, JT_OnPoActive; SetSwFocusBase passes 1 or 0 (W11: signature added) */
    virtual void SetPlayable(int vjoym); /* 79: SetPoPlayable; SetPoPlayable's caller passes 0 (W11: signature added) */
    virtual int FIsAvailable();         /* 80: func_001C41B8, JT_FIsPoAvailable; SetDprizeCharmDprizes tests the result (PRIVATE COPY: returned void in include/po.h) */
    virtual void Slot81(int first, int second); /* 81: func_001C4228 takes two ints and posts splice event 12 with their addresses; SetDprizeCharmDprizes passes the heal range (PRIVATE COPY: no arguments in include/po.h) */
    /* 0x150 */ struct JOY *pjoy;      /* the controller: UpdateLookRig, which calls JT slot 99 on the object */
    u8 unknown_0x154[0x8];
    /* 0x15C */ struct MAGNET magnet;   /* the collector record CpmagnetFindSwCollectors hands out the address of (FCheckDprizeMagnet reads a radius and geoms from it); PRIVATE COPY, W_new_1c3df8 */
    /* 0x168 */ struct PO *ppoSelf;     /* ClonePo (slot 41) stores the object itself here after the SO clone */
    /* 0x16C */ struct TN *ptn;        /* reader: OnPoActive, func_001C4130 (both PO methods/certain) */
    u8 unknown_0x170[0x4];
    /* 0x174 */ struct AMB *pamb;      /* reader: HandlePoMessage (PO slot 5) stops it on message 5 and clears the reference (PRIVATE COPY of include/po.h, W_new_1c3df8) */
    u8 unknown_0x178[0x8];
};

#if defined(__mips__)
SLY2_SIZE_CHECK(PO, 0x180);
SLY2_OFFSET_CHECK(PO, pjoy, 0x150);
SLY2_OFFSET_CHECK(PO, ptn, 0x16C);
SLY2_OFFSET_CHECK(PO, magnet, 0x15C);
SLY2_OFFSET_CHECK(PO, ppoSelf, 0x168);
SLY2_OFFSET_CHECK(PO, pamb, 0x174);
#endif
#endif
