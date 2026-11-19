// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
struct CFrame;
struct SLOTHEAP;
struct CPair { int m_cref; int m_unknown4; CRef m_ref; CPair *m_ppairNext; };
extern "C" {
CRef RefEval(CPair *ppair, CFrame *pframe);
void CRef_CopyConstruct(CRef *, CRef *);
void CRef_ConstructPair(CRef *, CPair *);
void SetTag__4CRef4TAGK(CRef *, int);
CPair *PpairNew(void);
void PairHandle_Assign(CPair **, CPair *);
CRef *bevy_splice_value_list_ref(CRef *, CPair *);
void CPairPtr_Destructor(CPair **, int);
void UnlinkPairNode(CPair *);
void CRef_Destruct(CRef *);
void FreeSlotheapPv(SLOTHEAP *, void *);
extern SLOTHEAP B_004520A8;
}
static inline void ReleasePair(CPair *held)
{
    if (held) {
        if (--held->m_cref == 0) {
            CPairPtr_Destructor(&held->m_ppairNext, 2);
            CRef_Destruct(&held->m_ref);
            UnlinkPairNode(held);
            FreeSlotheapPv(&B_004520A8, held);
        }
    }
}
struct PairHandle {
    CPair *p;
    PairHandle() {}
    PairHandle(const PairHandle &);
};
extern "C" {
PairHandle *func_00121578(PairHandle *, CRef **, CRef **);
void PairHandle_Init(PairHandle *, CPair *);
}
extern "C" CRef *RefOpFilter(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    if (aref[1].m_tagk == 0) {
        CRef_CopyConstruct(pref, &aref[1]);
        return pref;
    }
    PairHandle call;
    PairHandle result;
    CRef *prefCallee;
    CRef *prefArg;
    func_00121578(&call, &prefCallee, &prefArg);
    *prefCallee = aref[0];
    CPair *element = aref[1].m_tag.m_ppair;
    result.p = 0;
    CPair *tail;
    while (element != 0) {
        *prefArg = element->m_ref;
        CRef refCondition = RefEval(call.p, pframe);
        if (refCondition.m_tagk == TAGK_Bool && refCondition.m_tag.m_bool != 0) {
            PairHandle item;
            CPair *ppairItem = PpairNew();
            PairHandle_Init(&item, ppairItem);
            item.p->m_ref = element->m_ref;
            if (result.p == 0) {
                CPair *ppairHead = PpairNew();
                PairHandle_Assign(&result.p, ppairHead);
                bevy_splice_value_list_ref(&result.p->m_ref, item.p);
            } else {
                PairHandle_Assign(&tail->m_ppairNext, item.p);
            }
            CPair *ppairHeld = item.p;
            tail = ppairHeld;
            ReleasePair(ppairHeld);
        }
        element = element->m_ppairNext;
    }
    if (result.p == 0) {
        SetTag__4CRef4TAGK(pref, 0);
        ReleasePair(result.p);
        ReleasePair(call.p);
    } else {
        CRef_ConstructPair(pref, result.p->m_ref.m_tag.m_ppair);
        ReleasePair(result.p);
        ReleasePair(call.p);
    }
    return pref;
}
