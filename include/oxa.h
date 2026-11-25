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
    /* 0x64 */ struct NODE *first; /* readers: func_001F8E90, func_001F90D0 (the contact list; a source defines NODE) */
    /* 0x68 */ struct XP *own;     /* reader: func_001F90D0 (the object's own XP chain when the list is exhausted) */
    /* 0x6C */ struct MQ *pcontact; /* the contacts that absorbed the object: MarkSoCustomContacts adds to the list; func_001F7410 and so_sm_1f77c0 read it as pcontact */
    /* 0x70 */ u64 grf;          /* FFilterSensorSight, FFilterOxa (flags), PoxaAllocSw (grf), PoxaAllocLaser (sets 0x20) */
};
#endif
