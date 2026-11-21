// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CPair { int pad0; int pad4; CRef ref; CPair *next; };
struct CProc { int pad0; int pad4; int frame; int cArg; int fRest; int pad14; CPair *body; };
struct CMeth { int pad0; int pad4; int ctx; int fn; };
extern "C" void CRef_ConstructPair(CRef *, CPair *);
extern "C" CRef bevy_splice_bif_ref_equal(CRef *refA, CRef *refB)
{
    int f;
    if (refA->m_tagk != refB->m_tagk) {
        f = 0;
    } else {
        switch (refA->m_tagk) {
        case 0x1F: {
            CPair *pairA = (CPair *)refA->m_tag.m_n;
            CPair *pairB = (CPair *)refB->m_tag.m_n;
            if (pairA == pairB) {
                f = 1;
            } else if ((pairA->next == 0) != (pairB->next == 0)) {
                f = 0;
            } else {
                CRef result;
                result.m_tagk = TAGK_Nil;
                result = bevy_splice_bif_ref_equal(&pairA->ref, &pairB->ref);
                if (result.m_tag.m_n == 0) {
                    f = 0;
                } else if (pairA->next == 0) {
                    f = 1;
                } else {
                    CRef tailA;
                    CRef tailB;
                    CRef_ConstructPair(&tailA, pairA->next);
                    CRef_ConstructPair(&tailB, pairB->next);
                    result = bevy_splice_bif_ref_equal(&tailA, &tailB);
                    f = result.m_tag.m_n;
                }
            }
            break;
        }
        case 0x20: {
            CProc *procA = (CProc *)refA->m_tag.m_n;
            CProc *procB = (CProc *)refB->m_tag.m_n;
            if (procA == procB) {
                f = 1;
            } else if (procA->cArg != procB->cArg || procA->fRest != procB->fRest || procA->frame != procB->frame) {
                f = 0;
            } else {
                CRef bodyA;
                CRef bodyB;
                CRef_ConstructPair(&bodyA, procA->body);
                CRef_ConstructPair(&bodyB, procB->body);
                CRef bodies = bevy_splice_bif_ref_equal(&bodyA, &bodyB);
                f = bodies.m_tag.m_n;
            }
            break;
        }
        case 0x15: case 0x17: case 0x18: case 0x19: case 0x21:
            if (refA->m_tag.m_n == refB->m_tag.m_n) f = 1; else f = 0;
            break;
        case 0x22: {
            CMeth *methA = (CMeth *)refA->m_tag.m_n;
            CMeth *methB = (CMeth *)refB->m_tag.m_n;
            if (methA == methB) {
                f = 1;
            } else if (f = 0, methA->ctx == methB->ctx) {
                f = methA->fn == methB->fn;
            }
            break;
        }
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
        case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
        case 0x24:
            f = 1;
            break;
        default:
            break;
        }
    }
    return CRef(TAGK_Bool, f);
}
