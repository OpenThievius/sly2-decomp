/* SPDX-License-Identifier: GPL-3.0-or-later */
/* The button gadget. A BTN is the part both users keep in place: a BUTTON is an SO followed by its BTN at 0x150, a VOLBTN
   (the volume button, an XFM) keeps its BTN at 0x130; the functions of the Btn family take it. 0x158 bytes: from there each
   class has its own fields (BUTTON: its type, the objects and classes that may push it, an id and its target; VOLBTN: its own
   push lists). C++ derives BUTTON from SO (so.h); a C source reads the same layout through the C struct. */
#ifndef SLY2_BUTTON_H
#define SLY2_BUTTON_H
#ifdef __cplusplus
#include "lo.h"
#include "so.h"
#else
#include "types.h"
#endif
#include "rsmg.h"

struct BUTTON;

/* an (object id, argument) pair of a button's animation-segment list */
struct ASHENTRY {
    s32 oid;
    s32 nArg;
};

/* a list of up to eight pairs after its count: FAddAshOid (0x148620) appends one */
struct ASHLIST {
    u32 count;
    struct ASHENTRY aentry[8];
};

/* Readers: UpdateButton, FAbsorbButtonWkr, func_00149010, func_001492B0, RemoveVolbtn (buttons); CloneButton (pbutton);
   InitVolbtn, LoadVolbtnFromBrx (field_0x9C, field_0xA4); AddBtnAseg, AddBtnOffAseg (ashOn, ashOff: the Btn family's own functions). */
struct BTN {
    /* 0x00 */ struct BUTTON *pbutton; /* CloneButton points it at the button that owns it */
    /* 0x04 */ struct ASHLIST ashOn;   /* AddBtnAseg appends to it */
    /* 0x48 */ struct ASHLIST ashOff;  /* AddBtnOffAseg appends to it */
    /* 0x8C */ f32 field_0x8C; /* reader: InitBtn sets it to 1 (the Btn family's init) */
    /* 0x90 */ s32 buttons;   /* the pressed state UpdateButton and FAbsorbButtonWkr pass to SetButtonButtons */
    /* 0x94 */ f32 tButtons;  /* the time of the last change */
    /* 0x98 */ f32 dtRepush;  /* how long a mode 2 button waits before it can be pressed again; negative: never released */
    /* 0x9C */ s32 field_0x9C; /* InitVolbtn sets it to 1 */
    /* 0xA0 */ s32 fSeekEnd;  /* reader: RunBtnAsegs (a Btn family function, so the class is certain): the segments seek their end when set */
    /* 0xA4 */ s32 field_0xA4; /* LoadVolbtnFromBrx sets it to 1 */
    /* 0xA8 */ struct LO *pjsgSubject; /* reader: RunBtnAsegs passes it to StartJsg after pjsg */
    /* 0xAC */ void *pjsg;    /* reader: RunBtnAsegs: the joint sequence it starts */
    /* 0xB0 */ s32 crsmg;     /* readers: RunBtnAsegs passes it and arsmg to TriggerRsmg; SetAlarmRsmg passes both to FAddRsmg */
    /* 0xB4 */ struct RSMG arsmg[8]; /* readers: RunBtnAsegs (TriggerRsmg reads crsmg of them), SetAlarmRsmg (FAddRsmg, capacity 8) */
    /* 0x134 */ s32 ctaskreq; /* reader: RunBtnAsegs passes it and ataskreq to ApplyTaskStateRequests */
    /* 0x138 */ u8 ataskreq[0x20]; /* reader: RunBtnAsegs */
};

#ifdef __cplusplus
struct BUTTON : SO {
    /* 0x150 */ BTN btn;
    /* 0x2A8 */ s32 btnt;     /* the button's type (mode): UpdateButton, FAbsorbButtonWkr switch on it */
    /* 0x2AC */ s32 cploPush; /* FCheckButtonObject, func_00149220: the objects that may push it */
    /* 0x2B0 */ struct LO *aploPush[8];
    /* 0x2D0 */ s32 ccidPush; /* FCheckButtonObject, func_00149248: the classes that may push it */
    /* 0x2D4 */ s32 acidPush[8];
    /* 0x2F4 */ s32 id;       /* UpdateButton compares it with the game state's id */
    /* 0x2F8 */ struct SO *ptarget; /* UpdateButton stores the object that pushed it; func_00149010 clears it */
};
#else
struct BUTTON {
    u8 unknown_0x0[0x150];
    /* 0x150 */ struct BTN btn;
};
#endif

#ifdef __cplusplus
extern "C" s32 FAddAshOid(struct ASHLIST *pashlist, s32 oid, s32 nArg);
#else
s32 FAddAshOid(struct ASHLIST *pashlist, s32 oid, s32 nArg);
#endif

#if defined(__cplusplus) && defined(__mips__)
SLY2_SIZE_CHECK(BTN, 0x158);
SLY2_OFFSET_CHECK(BTN, ashOff, 0x48);
SLY2_OFFSET_CHECK(BTN, fSeekEnd, 0xA0);
SLY2_OFFSET_CHECK(BTN, arsmg, 0xB4);
SLY2_OFFSET_CHECK(BTN, ctaskreq, 0x134);
SLY2_OFFSET_CHECK(BTN, buttons, 0x90);
SLY2_OFFSET_CHECK(BUTTON, btn, 0x150);
SLY2_OFFSET_CHECK(BUTTON, btnt, 0x2A8);
SLY2_OFFSET_CHECK(BUTTON, ptarget, 0x2F8);
#endif
#endif
