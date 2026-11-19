// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
struct SLOTHEAP;
struct CPair;
struct PairHandle;
extern "C" {
CPair *PpairNew(void);
void CRef_ConstructPair(CRef *, CPair *);
void CPairPtr_Destructor(PairHandle *, int);
void UnlinkPairNode(CPair *);
void FreeSlotheapPv(SLOTHEAP *, void *);
int NRandInRange(int, int);
void PairHandle_Init(PairHandle *, CPair *);
void PairHandle_Assign(PairHandle *, CPair *);
extern SLOTHEAP B_004520A8;
}
// A counted handle to a pair: PairHandle_Init (0x256C38) is its constructor, PairHandle_Assign (0x256C58) its assignment, and
// the release block retail repeats for each handle is its inline destructor.
struct PairHandle {
    CPair *p;
    PairHandle() : p(0) {}
    PairHandle(CPair *pair) { PairHandle_Init(this, pair); }
    PairHandle(const PairHandle &other);
    void operator=(CPair *pair) { PairHandle_Assign(this, pair); }
    ~PairHandle();
};
struct CPair { int m_cref; int m_unknown4; CRef m_ref; PairHandle m_ppairNext; };
inline PairHandle::~PairHandle()
{
    CPair *held = p;
    if (held) {
        if (--held->m_cref == 0) {
            CPairPtr_Destructor(&held->m_ppairNext, 2);
            held->m_ref.Decref();
            UnlinkPairNode(held);
            FreeSlotheapPv(&B_004520A8, held);
        }
    }
}
// A ref built with its tag: cref.h's CRef lacks the constructor CRef(TAGK) that sets it.
struct CRefTag : CRef {
    CRefTag(TAGK tagk) { SetTag(tagk); }
};
// Shuffles the elements of a list: drops nil elements, permutes the rest at random (never leaving the first in place), and
// returns them as a new list.
extern "C" CRef *bevy_splice_bif_bif41_shuffle(CRef *pret, int carg, CRef *aref)
{
    if (aref->m_tagk == 0) {
        pret->SetTag((TAGK)0);
    } else if (aref->m_tagk != TAGK_Pair) {
        pret->SetTag((TAGK)0);
    } else {
        CRef *items[0x80];
        int count = 0;
        int zeroIndex = -1;
        for (CPair *node = aref->m_tag.m_ppair; node != 0; node = node->m_ppairNext.p) {
            if (node->m_ref.m_tagk == 0)
                zeroIndex = count;
            else
                items[count++] = &node->m_ref;
        }
        int fshuffle = count >= 2 && zeroIndex < 1;
        if (fshuffle) {
            CRef *first = items[0];
            for (int round = 0; round < count; round++) {
                int pick = NRandInRange(0, count - 1);
                CRef *held = items[pick];
                items[pick] = items[round];
                items[round] = held;
            }
            if (items[0] == first) {
                items[0] = items[count - 1];
                items[count - 1] = first;
            }
            zeroIndex = count;
        }
        PairHandle head;
        PairHandle *tail = &head;
        CPair *target = 0;
        for (int index = 0; index < count; index++) {
            *tail = PpairNew();
            CPair *node = tail->p;
            tail = &node->m_ppairNext;
            node->m_ref = *items[index];
            if (index == zeroIndex - 1)
                target = node;
        }
        if (target != 0 && target != head.p) {
            if (!fshuffle) {
                PairHandle *next = &target->m_ppairNext;
                PairHandle second(head.p);
                head = head.p->m_ppairNext.p;
                second.p->m_ppairNext = next->p;
                *next = second.p;
            }
            if (head.p != target) {
                PairHandle *next = &target->m_ppairNext;
                PairHandle second(PpairNew());
                second.p->m_ref = CRefTag((TAGK)0);
                second.p->m_ppairNext = next->p;
                *next = second.p;
            }
        }
        CRef_ConstructPair(pret, head.p);
    }
    return pret;
}
