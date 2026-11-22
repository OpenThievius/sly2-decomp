// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "crefboxes.h"
#include "timedcall.h"
#include "sw.h"

/* the boxes behind the payload pointers that CRefboxes.h does not have: a reference count after the value */
struct LM {
    u8 unknown_0x0[0x8];
    s32 cref;
};

struct SMP {
    u8 unknown_0x0[0xC];
    s32 cref;
};

struct CProc {
    s32 cref;
};

struct CMethod {
    s32 cref;
};

extern "C" {
void CPairPtr_Destructor(CPair **ppair, s32 flags);
void CProc_DeletingDestructor(CProc *pproc, s32 flags);
void FreeSlotheapPv(SLOTHEAP *pslotheap, void *pv);
void UnlinkPairNode(CPair *ppair);
void func_00256120(CMethod *pmethod);
extern SLOTHEAP B_004520A8;
extern SLOTHEAP B_00452170;
extern SLOTHEAP B_00452188;
extern SLOTHEAP B_004521A0;
extern SLOTHEAP B_004521B8;
extern SLOTHEAP B_004521D0;
extern SLOTHEAP B_004521E8;

void CRef_Destruct(CRef *pref) {
    switch (pref->m_tagk) {
    case TAGK_Vector:
        {
            VECTORBOX *pvectorbox = (VECTORBOX *)pref->m_tag.m_pvector;
            if (--pvectorbox->cref == 0) {
                FreeSlotheapPv(&B_00452188, pvectorbox);
            }
        }
    default:
        break;
    case TAGK_Matrix:
        {
            MATRIXBOX *pmatrixbox = (MATRIXBOX *)pref->m_tag.m_pmatrix;
            if (--pmatrixbox->cref == 0) {
                FreeSlotheapPv(&B_004521A0, pmatrixbox);
            }
        }
        break;
    case TAGK_Clq:
        {
            CLQBOX *pclqbox = (CLQBOX *)pref->m_tag.m_pclq;
            if (--pclqbox->cref == 0) {
                FreeSlotheapPv(&B_004521B8, pclqbox);
            }
        }
        break;
    case TAGK_Lm:
        {
            LM *plm = pref->m_tag.m_plm;
            if (--plm->cref == 0) {
                FreeSlotheapPv(&B_004521D0, plm);
            }
        }
        break;
    case TAGK_Smp:
        {
            SMP *psmp = pref->m_tag.m_psmp;
            if (--psmp->cref == 0) {
                FreeSlotheapPv(&B_004521E8, psmp);
            }
        }
        break;
    case TAGK_Pair:
        {
            CPair *ppair = pref->m_tag.m_ppair;
            if ((--ppair->cref == 0) && (ppair != 0)) {
                CPairPtr_Destructor(&ppair->next, 2);
                CRef_Destruct(&ppair->ref);
                UnlinkPairNode(ppair);
                FreeSlotheapPv(&B_004520A8, ppair);
            }
        }
        break;
    case TAGK_Proc:
        {
            CProc *pproc = pref->m_tag.m_pproc;
            if (--pproc->cref == 0) {
                if (pproc != 0) {
                    CProc_DeletingDestructor(pproc, 3);
                }
            }
        }
        break;
    case TAGK_Basic:
        {
            BASIC *pbasic = pref->m_tag.m_pbasic;
            if (pbasic != 0) {
                pbasic->Slot2();
            }
        }
        break;
    case TAGK_Method:
        {
            CMethod *pmethod = pref->m_tag.m_pmethod;
            if ((--pmethod->cref == 0) && (pmethod != 0)) {
                func_00256120(pmethod);
                FreeSlotheapPv(&B_00452170, pmethod);
            }
        }
        break;
    }
}

}
