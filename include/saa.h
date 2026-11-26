/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SAA, a screen animation node (retail "saa"): a BASIC whose slot 7 reads its record; subclasses add their own fields at 0x50.
   The layout is the one src/new_1ed1a8/new_1ed1a8_1ed7a8.cpp declares locally (InitSaa, FUpdatableSaa, SetSaiIframe, SetSaiDuDv,
   FlushSaaUnpacks, FMatchesSaaOid); UpdateSaas (0x30 as a flag, 0x40 next) and PsaaFromOid (oid, owner, next) agree on the offsets
   they read. C++ only. */
#ifndef SLY2_SAA_H
#define SLY2_SAA_H
#include "types.h"
#include "lo.h"
#include "sl.h"

struct SAA : BASIC {
    virtual void LoadFromRecord(void *precord); /* 7: func_001ED7A8 calls it with the 0x20-byte record it just read */
    virtual void Update();                      /* 8: UpdateSaas calls it on each node FUpdatableSaa accepts */
    /* 0x10 */ f32 tLast;          /* FUpdatableSaa: the clock time of the last update */
    /* 0x14 */ s32 oid;            /* InitSaa copies it from the record; FMatchesSaaOid, PsaaFromOid */
    /* 0x18 */ s32 field_0x18;     /* InitSaa copies it from the record */
    /* 0x1C */ s32 cframe;         /* the frame count: InitSaa copies it from the record; SetSaiIframe, UpdateLoop */
    /* 0x20 */ s32 field_0x20;     /* InitSaa copies it from the record */
    /* 0x24 */ s16 du;             /* SetSaiDuDv: 12-bit fixed point */
    /* 0x26 */ s16 dv;
    /* 0x28 */ u16 iframe;         /* SetSaiIframe */
    u8 unknown_0x2A[0x2];
    /* 0x2C */ s32 fDirty;         /* SetSaiIframe, SetSaiDuDv set it; FlushSaaUnpacks clears it */
    /* 0x30 */ SAA *owner;         /* func_001ED7A8 sets it; InitSaa appends the node to the list only when it has none; UpdateSaas and PsaaFromOid test it */
    /* 0x34 */ SL sl;              /* InitSaa: InitSl(.., 0x10), the node's pending unpacks */
    /* 0x40 */ SAA *next;          /* the link in B_003E159C's list (FlushSaaUnpacks, UpdateSaas, PsaaFromOid) */
    u8 unknown_0x44[0xC];
};
#endif
