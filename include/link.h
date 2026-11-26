/* SPDX-License-Identifier: GPL-3.0-or-later */
/* LINK, the region link of a solid object's PHYS (PHYS::plink, phys.h), 0x70 bytes: func_001F8300 allocates it (PvAllocSwClearImpl) for the first
   caller that needs one. Until now every reader declared the part it reads (func_0017C3E8, func_0017E458, func_0017D8A8, func_001F37C8,
   GoalPartnerFollow_PpathzoneTarget); fields from those readers. C and C++. */
#ifndef SLY2_LINK_H
#define SLY2_LINK_H
#include "types.h"

struct PATHZONE;
struct SO;

struct LINK {
    /* 0x00 */ struct SO *pso;        /* func_001F8300 sets it to the object */
    /* 0x04 */ f32 field_0x4;         /* func_001F8470 sets it, func_001F84A0 reads it (0 without a link) */
    /* 0x08 */ f32 field_0x8;         /* func_001F8300 sets 150.0 (class 0x34) or 75.0; func_001F83B0 sets it, func_001F83E0 reads it */
    /* 0x0C */ f32 field_0xC;         /* func_001F8300 sets 1.0; func_001F8410 sets it, func_001F8440 reads it */
    /* 0x10 */ struct PATHZONE *zone; /* the region: func_0017C3E8, func_0017E458, func_0017D8A8, func_001F37C8, GoalPartnerFollow_PpathzoneTarget read it */
    u8 unknown_0x14[0x5C];
};

#if defined(__mips__)
typedef char check_LINK_zone[((unsigned int)&((struct LINK *)0)->zone == 0x10) ? 1 : -1];
typedef char check_LINK_size[(sizeof(struct LINK) == 0x70) ? 1 : -1];
#endif
#endif
