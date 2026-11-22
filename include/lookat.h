/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LOOKAT, a look-at act: an act on an XF (InsertXfAct / RemoveXfAct list it on XF::pactFirst) that aims the transform. The
   first 0x1C bytes are the act base every kind shares; from 0x1C on each kind has its own fields (CloneAct copies them as one
   block, whose size retail keeps in B_003E123C). C and C++ (LOOKATGOAL C++ only). */
#ifndef SLY2_LOOKAT_H
#define SLY2_LOOKAT_H
#include "sly2.h"

struct ALO;
struct XF;

struct LOOKAT {
    /* 0x00 */ s32 lookatk;               /* the kind: CloneAct copies it, FActDrivesXf tests 5 */
    /* 0x04 */ struct ALO *palo;          /* the object whose transform it drives: CloneAct, ActivateAct, AddLookat, RemoveLookat */
    /* 0x08 */ struct XF *pxf;            /* the transform it acts on: same readers, FLookatInList, func_0012D088, func_0012CF30 */
    /* 0x0C */ s32 priority;              /* CloneAct copies it (InsertXfAct sorts the list by an act's word at 0xC) */
    /* 0x10 */ struct LOOKAT *plookatNext; /* the next act on the same XF: FLookatInList */
    /* 0x14 */ s32 xfkind;                /* ActivateAct passes it to SetXfKind; CloneAct copies it */
    u8 unknown_0x18[0x4];
};

#ifdef __cplusplus
/* the lookat kind that drives its XF's goal: its own fields start at 0x1C (a JUMPER keeps one, JUMPER::plookat) */
struct LOOKATGOAL : LOOKAT {
    /* 0x1C */ u16 xfSub;                /* func_0012D088 copies it to XF::sub */
    u8 unknown_0x1E[0x2];
    /* 0x20 */ QW posTarget;             /* func_0012D088 copies it to XF::posGoal; func_0012D0D8 reads it; SetJumperTarget sets it */
};
#endif
#endif
