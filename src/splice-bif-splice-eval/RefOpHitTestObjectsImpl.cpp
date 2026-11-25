#include "sly2.h"
#include "cref.h"
#include "timedcall.h"
#include "geom.h"
#include "so.h"
struct PairHandle;
struct SLOTHEAP;
struct CLIP { QW pos; QW normal; QW rest[4]; };
extern "C" {
CPair *PpairNew(void);
void PairHandle_Assign(CPair **, CPair *);
void CPairPtr_Destructor(CPair **, int);
void UnlinkPairNode(CPair *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void CRef_SetVectorPtr(CRef *, QW *);
CRef *bevy_splice_value_list_ref(CRef *, CPair *);
int ClsgClipEdgeToObject(GEOM *, QW, QW, int, CLIP *);
extern SLOTHEAP B_004520A8;
}
static inline void ReleasePair_1249A8(CPair *held)
{
    if (held) {
        if (--held->cref == 0) {
            CPairPtr_Destructor(&held->next, 2);
            held->ref.Decref();
            UnlinkPairNode(held);
            FreeSlotheapPv(&B_004520A8, held);
        }
    }
}
struct PairHandle {
    CPair *p;
    int pad[3];
    PairHandle(CPair *) asm("PairHandle_Init");
    ~PairHandle() { ReleasePair_1249A8(p); }
};
extern "C" CRef RefOpHitTestObjectsImpl(int op, int unused, CRef *aref)
{
    CRef result;
    result.m_tagk = TAGK_Nil;
    if (aref[0].m_tagk == 0) {
        result = aref[0];
    } else {
        PairHandle first(0);
        PairHandle last(0);
        CLIP clip;
        for (CPair *node = aref[0].m_tag.m_ppair; node != 0; node = node->next) {
            CRef *pend = &aref[2];
            SO *pobj = (SO *)node->ref.m_tag.m_pbasic;
            if (pobj != 0) {
                for (int index = 0; index < pobj->cgeom; index++) {
                    GEOM *pelem = &pobj->ageom[index];
                    CRef *pstart = &aref[1];
                    if (!(pelem->grf & (0x8000L << 35)) &&
                        ClsgClipEdgeToObject(pelem, *(QW *)pstart->m_tag.m_pvector, *(QW *)pend->m_tag.m_pvector, 1, &clip) > 0) {
                        CPair *pnewA = PpairNew();
                        PairHandle pairA(pnewA);
                        CPair *pnewB = PpairNew();
                        PairHandle pairB(pnewB);
                        pairA.p->ref.SetBasic(pobj);
                        PairHandle_Assign(&pairA.p->next, pairB.p);
                        if (op == 0x7B) {
                            CPair *pnewC = PpairNew();
                        PairHandle pairC(pnewC);
                            CPair *pnewD = PpairNew();
                        PairHandle pairD(pnewD);
                            CRef_SetVectorPtr(&pairB.p->ref, &clip.pos);
                            PairHandle_Assign(&pairB.p->next, pairC.p);
                            CRef_SetVectorPtr(&pairC.p->ref, &clip.normal);
                            bevy_splice_value_list_ref(&pairD.p->ref, pairA.p);
                            if (first.p != 0)
                                PairHandle_Assign(&last.p->next, pairD.p);
                            else
                                PairHandle_Assign(&first.p, pairD.p);
                            PairHandle_Assign(&last.p, pairD.p);
                        } else {
                            CRef_SetVectorPtr(&pairB.p->ref, &clip.normal);
                            bevy_splice_value_list_ref(&result, pairA.p);
                            return result;
                        }
                    }
                }
            }
        }
        if (first.p != 0)
            bevy_splice_value_list_ref(&result, first.p);
        else
            result.m_tagk = (TAGK)0;
    }
    return result;
}
