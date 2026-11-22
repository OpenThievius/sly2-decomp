/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C view of AMB (amb.h), which is C++ only: the fields of an ambient emitter the C sources read: the sound driver's voice id at
   0x40 (AMB::voice; ContinueAmbVoice, PauseAmbVoice hand it to the driver) and the reference count at 0x4C (AMB::cRef; AMB_AddRef,
   StreamAmb_AddRef). A C++ source uses AMB itself. C only. */
#ifndef SLY2_AMBVIEW_H
#define SLY2_AMBVIEW_H
#ifdef __cplusplus
#error "ambview.h is the C view of amb.h: include amb.h in C++"
#endif
#include "types.h"

struct AMBVIEW {
    u8 unknown_0x0[0x40];
    /* 0x40 */ s32 voice; /* AMB::voice */
    u8 unknown_0x44[8];
    /* 0x4C */ u16 cRef; /* AMB::cRef */
};
#endif
