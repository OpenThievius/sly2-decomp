// SPDX-License-Identifier: GPL-3.0-or-later
/* HUDLABEL, the HUD's label slot (0x2C bytes; InitHudLabel, ClearHudLabel, SetHudLabelState, ShowHudLabel, UpdateHudLabel): a
   label shown through a blot, the one waiting behind it. Our name; fields from SetHudLabelState (state, tState, label, tHold,
   labelNext, tHoldNext, pblot) and the two functions here that agree with it. C++ only. */
#ifndef SLY2_HUDLABEL_H
#define SLY2_HUDLABEL_H
#include "blot.h"
struct HUDLABEL {
    u8 unknown_0x0[0x10];
    /* 0x10 */ s32 state;        /* 0 idle, 1 appearing, 2 shown, 3 leaving, 4 switching: ShowHudLabel, UpdateHudLabel, SetHudLabelState */
    /* 0x14 */ f32 tState;       /* UpdateHudLabel advances it while shown */
    /* 0x18 */ s32 label;        /* ShowHudLabel sets the label id shown; SetHudLabelState */
    /* 0x1C */ f32 tHold;        /* ShowHudLabel: the value (how long it is held); UpdateHudLabel */
    /* 0x20 */ s32 labelNext;    /* ShowHudLabel queues the next label id; UpdateHudLabel switches to it (-1: none) */
    /* 0x24 */ f32 tHoldNext;    /* ShowHudLabel: the queued label's value */
    /* 0x28 */ BLOT *pblot;      /* UpdateHudLabel, SetHudLabelState */
};
#endif
