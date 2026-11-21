#include "sly2.h"
#include "cref.h"
struct Frame;
struct Pair;
struct SLOTHEAP;
struct HP { Pair *p; int pad[3]; };
struct Proc { int cref; };
extern "C" {
void CRef_ConstructVector(CRef *, void *);
void CRef_ConstructMatrix(CRef *, void *);
void CRef_ConstructClq(CRef *, void *);
void CRef_ConstructLm(CRef *, void *);
void CRef_ConstructSmp(CRef *, void *);
void CRef_ConstructPair(CRef *, Pair *);
void CRef_ConstructProc(CRef *, Proc *);
void CRef_ConstructBasic(CRef *, void *);
void CRef_CopyConstruct(CRef *, CRef *);
void PpairClone(HP *, void *, Frame *, unsigned long);
void PprocClone(Proc **, void *, Frame *);
void CPairPtr_Destructor(Pair **, int);
void UnlinkPairNode(Pair *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void CProc_DeletingDestructor(Proc *, int);
extern SLOTHEAP B_004520A8;
}
struct PairView { int cref; int pad4; CRef ref; Pair *next; };
extern "C" CRef *CRef_RefClone(CRef *pref, CRef *ref, Frame *pframe, unsigned long ulArg)
{
    switch (ref->m_tagk) {
    case TAGK_Vector:
        CRef_ConstructVector(pref, (void *)ref->m_tag.m_n);
        return pref;
    case TAGK_Matrix:
        CRef_ConstructMatrix(pref, (void *)ref->m_tag.m_n);
        return pref;
    case TAGK_Clq:
        CRef_ConstructClq(pref, (void *)ref->m_tag.m_n);
        return pref;
    case TAGK_Lm:
        CRef_ConstructLm(pref, (void *)ref->m_tag.m_n);
        return pref;
    case TAGK_Smp:
        CRef_ConstructSmp(pref, (void *)ref->m_tag.m_n);
        return pref;
    case TAGK_Pair: {
        HP clone;
        PpairClone(&clone, (void *)ref->m_tag.m_n, pframe, ulArg);
        CRef_ConstructPair(pref, clone.p);
        PairView *held = (PairView *)clone.p;
        if (held) {
            if (--held->cref == 0) {
                CPairPtr_Destructor(&held->next, 2);
                held->ref.Decref();
                UnlinkPairNode((Pair *)held);
                FreeSlotheapPv(&B_004520A8, held);
            }
        }
        return pref;
    }
    case TAGK_Proc: {
        struct { Proc *p; int pad[3]; } cloneBox;
        PprocClone(&cloneBox.p, (void *)ref->m_tag.m_n, pframe);
        CRef_ConstructProc(pref, cloneBox.p);
        Proc *held = cloneBox.p;
        if (held) {
            if (--held->cref == 0)
                CProc_DeletingDestructor(held, 3);
        }
        return pref;
    }
    case TAGK_Basic:
        CRef_ConstructBasic(pref, (void *)ref->m_tag.m_n);
        return pref;
    default:
        CRef_CopyConstruct(pref, ref);
        return pref;
    }
}
