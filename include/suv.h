/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SUV (class name from CloneSuv): only what CloneSuv, a method of the class, reads. C only. */
#ifndef SLY2_SUV_H
#define SLY2_SUV_H
#include "types.h"

struct SUV {
    u8 unknown_0x0[0xE4];
    /* 0xE4 */ s32 *pcshare; /* a count shared by an object and its clones: CloneSuv increments it */
};
#endif
