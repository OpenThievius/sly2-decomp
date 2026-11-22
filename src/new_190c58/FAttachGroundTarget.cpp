// SPDX-License-Identifier: GPL-3.0-or-later
#include "attach.h"
// A candidate of the world's target list (SW::atgt, 0x30 bytes) as this function reads it: word 0 an object it passes to
// FIsBasicDerivedFrom (UpdateSwTargetList reads the same word as an object id, TGT::oid), word 1 a member index, word 2 the distance (TGT::sRank).
struct TARGETVIEW { LO *plo; s32 imember; float dist; u8 unknown_0xC[0x30 - 0xC]; };
extern SW B_003DD490;
extern SLY *g_2e1e40; /* the player */
extern float D_FLT_002BF660;
extern "C" {
int FIsBasicDerivedFrom(void *, int);
}
int FAttachGroundTarget(ATTACH *pattach)
{
    int itarget = 0;
    int ctarget = B_003DD490.ctgt;
    for (; itarget < ctarget; itarget++) {
        TARGETVIEW *ptarget = (TARGETVIEW *)&B_003DD490.atgt[itarget];
        if (ptarget->dist > D_FLT_002BF660)
            break;
        LO *plo = ptarget->plo;
        int kind;
        if (FIsBasicDerivedFrom(plo, 0x13) || FIsBasicDerivedFrom(plo, 0xB)) {
            kind = pattach->pjt == g_2e1e40 ? 6 : 5;
        } else if (FIsBasicDerivedFrom(plo, 0x1B)) {
            kind = 8;
        } else if (FIsBasicDerivedFrom(plo, 0xC) || FIsBasicDerivedFrom(plo, 0x22)) {
            kind = 0;
        } else if (FIsBasicDerivedFrom(plo, 0x26)) {
            kind = *(int *)((char *)ptarget->plo + 0x10C);
        } else if (FIsBasicDerivedFrom(plo, 0x23)) {
            kind = 7;
        } else {
            kind = -1;
        }
        if (kind != -1) {
            StartAttach(pattach, kind, plo, ptarget->imember);
            return 1;
        }
    }
    return 0;
}
