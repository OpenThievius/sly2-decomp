/* SPDX-License-Identifier: GPL-3.0-or-later */
/* OXA, the contact record of a solid object (what SO::PoxaAlloc, slot 53, allocates: PoxaAllocSo, PoxaAllocSw, PoxaAllocLaser; SO::poxa
   points at it), and OX, one node of its list of pairs (OXA::first). PoxaAllocSw takes an OXA from SW::slotheapOxa (0x80-byte slots) and
   links it into the world's lists; AllocSwOx takes an OX from SW::slotheapOx (0x14-byte slots: Sw_Construct). Names are ours (source:
   the recovered function names AllocSwOx, PoxExtractFromPoxa, UpdateSwPox, PmqFirstOxaContact) and the fields' from their readers.
   Each source used to declare its own view of both (POXA and OX in PoxaAllocSw_file.cpp, NODE in the readers of OXA::first). C++ only. */
#ifndef SLY2_OXA_H
#define SLY2_OXA_H
#include "types.h"
#include "dl.h"

struct SO;
struct XP;

/* One pair of objects in contact, seen from one of them (0x14 bytes). UpdateSwPox creates the two nodes of a pair together (AllocSwOx
   on each object's OXA, each node's pair pointing at the other) and frees both; the pair's contact list is stored in both nodes. */
struct OX {
    /* 0x00 */ struct XP *pxp;  /* the chain of contacts (XP, include/xp.h) of the pair: RecalcSwXpAll stores it in both nodes, DiscardSoXps
                                   and UpdateSwPox free it, func_001F8E90, func_001F90D0, AdjustStepXps, UpdateButton, NotifyBarrierImpact,
                                   func_00144640 and func_00199298 walk it; func_001F4F10, PmqFirstOxaContact and NNextSensorState test it */
    /* 0x04 */ OX *next;        /* the next node of the object's list: AllocSwOx pushes, PoxExtractFromPoxa unlinks, every reader walks */
    /* 0x08 */ OX *pair;        /* the other object's node of the same pair: UpdateSwPox links the two, RecalcSwXpAll stores the chain in
                                   it, DiscardSoXps clears its chain, AdjustStepXps and func_00199298 write their chain back to it */
    /* 0x0C */ struct SO *pso;  /* the other object: AllocSwOx, PoxExtractFromPoxa and UpdateSwPox (the key), DiscardSoXps, func_001F8E90,
                                   func_001F90D0, RecalcSwXpAll, NNextSensorState */
    /* 0x10 */ s32 flag;        /* UpdateSwPox: the pair's forced state, set in both nodes */
};

struct OXA {
    /* 0x00 */ f32 aMin[3];         /* the bounds' low corner: PoxaAllocSw (the world's axis lists point at each coordinate), FPoxaPairInteracts */
    u8 unknown_0xC[0x4];
    /* 0x10 */ f32 aMax[3];         /* the high corner: the same readers */
    u8 unknown_0x1C[0x18];
    /* 0x34 */ struct DL dlGeom;    /* the geometry entered in the record: AddSoGeomToOxa (FFindDlEntry, AppendDlEntry), RemoveSoGeomFromOxa (FFindDlEntry,
                                       RemoveDlEntry, FIsDlEmpty); a method of SO (poxa's owner) in both; PoxaAllocSw: InitDl(.., 0x60) */
    u8 unknown_0x40[0x8];
    /* 0x48 */ OXA *pnext;          /* the link of SW::dlOxa (Sw_Construct: ibDle 0x48): RecalcSwOxfFilterForObject */
    u8 unknown_0x4C[0xC];           /* 0x50: the link of SW::dlOxaRecalc (ibDle 0x50) */
    /* 0x58 */ OXA *pnextDirty;     /* the link of SW::dlOxaDirty (ibDle 0x58): RecalcSwXpAll */
    u8 unknown_0x5C[0x4];
    /* 0x60 */ struct SO *owner;    /* RecalcSoLocked, DiscardSoXps, FFilterOxa (as so), PoxaAllocSw (owner), UpdateSwPox, FPoxaPairInteracts */
    /* 0x64 */ OX *first;           /* the object's pairs (OX): AllocSwOx, PoxExtractFromPoxa, UpdateSwPox, RecalcSwXpAll, DiscardSoXps,
                                       func_001F4F10, func_001F8E90, func_001F90D0, AdjustStepXps, UpdateButton, NotifyBarrierImpact,
                                       func_00144640, PmqFirstOxaContact, func_00199298, NNextSensorState */
    /* 0x68 */ struct XP *own;      /* the object's contacts outside any pair: func_001F90D0 and AdjustStepXps walk it after the pairs,
                                       DiscardSoXps and RecalcSwXpAll free it */
    /* 0x6C */ struct XP *pcontact; /* the contacts (XP, include/xp.h) that absorbed the object: MarkSoCustomContacts adds to the list; func_001F7410 and so_sm_1f77c0 read it as pcontact */
    /* 0x70 */ u64 grf;             /* FFilterSensorSight, FFilterOxa (flags), PoxaAllocSw (grf), PoxaAllocLaser (sets 0x20), RecalcSwXpAll (bits 2, 8, 0x10) */
};

#if defined(__mips__)
typedef char check_OX_size[(sizeof(OX) == 0x14) ? 1 : -1];
typedef char check_OXA_first[((unsigned int)&((OXA *)0)->first == 0x64) ? 1 : -1];
typedef char check_OXA_grf[((unsigned int)&((OXA *)0)->grf == 0x70) ? 1 : -1];
#endif
#endif
