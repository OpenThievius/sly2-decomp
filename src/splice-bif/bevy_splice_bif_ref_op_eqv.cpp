// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
struct CFrame;
extern "C" CRef bevy_splice_bif_ref_op_eqv(int cref, CRef *aref, CFrame *pframe) return ref
{
    CRef *refB = aref + 1;
    int f;
    if (aref->m_tagk != refB->m_tagk) {
        f = 0;
    } else {
        switch (aref->m_tagk) {
        case 0x15: case 0x17: case 0x18: case 0x19:
            f = aref->m_tag.m_n == refB->m_tag.m_n;
            break;
        case 0x1F:
            f = aref->m_tag.m_ppair == refB->m_tag.m_ppair;
            break;
        case 0x20:
            f = aref->m_tag.m_pproc == refB->m_tag.m_pproc;
            break;
        case 0x21:
            f = aref->m_tag.m_pbasic == refB->m_tag.m_pbasic;
            break;
        case 0x22:
            f = aref->m_tag.m_pmethod == refB->m_tag.m_pmethod;
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
        case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
        case 0x24:
            f = 1;
            break;
        }
    }
    ref.m_tag.m_n = f;
    ref.m_tagk = TAGK_Bool;
}
