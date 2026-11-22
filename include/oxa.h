/* SPDX-License-Identifier: GPL-3.0-or-later */
/* OXA, the contact record of a solid object (what SO::PoxaAlloc, slot 53, allocates: PoxaAllocSo, PoxaAllocSw, PoxaAllocLaser; SO::poxa
   points at it). Only the fields several functions read are declared; each source used to declare its own view of the object. C++ only. */
#ifndef SLY2_OXA_H
#define SLY2_OXA_H
#include "types.h"

struct SO;

struct OXA {
    u8 unknown_0x0[0x60];
    /* 0x60 */ struct SO *owner; /* RecalcSoLocked, DiscardSoXps, FFilterOxa (as so), PoxaAllocSw (owner) */
    u8 unknown_0x64[0xC];
    /* 0x70 */ u64 grf;          /* FFilterSensorSight, FFilterOxa (flags), PoxaAllocSw (grf), PoxaAllocLaser (sets 0x20) */
};
#endif
