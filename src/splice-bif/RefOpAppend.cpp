#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
struct PairHandle { CPair *p; int pad[3]; };
struct SLOTHEAP;
struct CFrame;
extern "C" {
CPair *PpairNew(void);
void PairHandle_Assign(CPair **, CPair *);
void PpairClone(PairHandle *, int, CFrame *, u64);
void CRef_Destruct(CRef *);
void CPairPtr_Destructor(CPair **, int);
void UnlinkPairNode(CPair *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void SetTag__4CRef4TAGK(CRef *, int);
void CRef_ConstructPair(CRef *, CPair *);
void CRef_CopyConstruct(CRef *, CRef *);
CRef *bevy_splice_value_list_ref(CRef *, CPair *);
extern SLOTHEAP B_004520A8;
}
static inline void ReleasePair(CPair *held)
{
    if (held) {
        if (--held->cref == 0) {
            CPairPtr_Destructor(&held->next, 2);
            CRef_Destruct(&held->ref);
            UnlinkPairNode(held);
            FreeSlotheapPv(&B_004520A8, held);
        }
    }
}
extern "C" CRef *RefOpAppend(CRef *pret, int carg, CRef *aref)
{
    PairHandle result;
    PairHandle copy;
    PairHandle clone;
    if (aref->m_tagk == 0) {
        CRef_CopyConstruct(pret, aref);
        return pret;
    }
    CPair *tail;
    result.p = 0;
    for (CPair *node = aref->m_tag.m_ppair; node != 0; node = node->next) {
        if (node->ref.m_tagk == 0x1F) {
            copy.p = 0;
            if (node->next != 0) {
                PpairClone(&clone, node->ref.m_tag.m_n, 0, 0);
                PairHandle_Assign(&copy.p, clone.p);
                ReleasePair(clone.p);
            } else {
                PairHandle_Assign(&copy.p, node->ref.m_tag.m_ppair);
            }
            if (result.p == 0) {
                PairHandle_Assign(&result.p, PpairNew());
                bevy_splice_value_list_ref(&result.p->ref, copy.p);
            } else {
                PairHandle_Assign(&tail->next, copy.p);
            }
            tail = copy.p;
            while (tail->next != 0)
                tail = tail->next;
            ReleasePair(copy.p);
        }
    }
    if (result.p == 0) {
        SetTag__4CRef4TAGK(pret, 0);
        ReleasePair(result.p);
    } else {
        CRef_ConstructPair(pret, result.p->ref.m_tag.m_ppair);
        ReleasePair(result.p);
    }
    return pret;
}
