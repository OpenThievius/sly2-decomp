/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cref.h"

/* timedcall.h's CPair (C++ only): a reference count, a CRef and the next pair of the list. */
struct CPair {
    /* 0x00 */ s32 cref;
    u8 unknown_0x4[0x4];
    /* 0x08 */ struct CRef ref;
    /* 0x10 */ struct CPair *next;
};

struct CRef *CRef_ConstructPair(struct CRef *pref, struct CPair *ppair);
void SetTag__4CRef4TAGK(struct CRef *pref, enum TAGK tagk);

struct CRef *RefOpCdr(struct CRef *pref, s32 carg, struct CRef *aref) {
    struct CPair *pnext;

    pnext = aref->m_tag.m_ppair->next;
    if (pnext == 0) {
        SetTag__4CRef4TAGK(pref, 0);
    } else {
        CRef_ConstructPair(pref, pnext);
    }
    return pref;
}
