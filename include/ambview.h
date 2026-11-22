/* SPDX-License-Identifier: GPL-3.0-or-later */
/* C view of AMB (amb.h), which is C++ only: the one field of an ambient emitter the C sources read, the sound driver's voice id at
   0x40 (AMB::voice). Readers: ContinueAmbVoice, PauseAmbVoice (both hand it to the driver). A C++ source uses AMB itself. C only. */
#ifndef SLY2_AMBVIEW_H
#define SLY2_AMBVIEW_H
#ifdef __cplusplus
#error "ambview.h is the C view of amb.h: include amb.h in C++"
#endif
#include "types.h"

struct AMBVIEW {
    u8 unknown_0x0[0x40];
    /* 0x40 */ s32 voice; /* AMB::voice */
};
#endif
