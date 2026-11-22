// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CPair { int cref; int pad4; CRef ref; CPair *next; };
struct PairHandle { CPair *p; int pad; };
struct CFrame;
struct SLOTHEAP;
extern "C" {
PairHandle *func_00121578(PairHandle *, CRef **, CRef **);
CRef RefEval(CPair *, CFrame *);
void CPairPtr_Destructor(CPair **, int);
void UnlinkPairNode(CPair *);
void FreeSlotheapPv(SLOTHEAP *, void *);
extern SLOTHEAP B_004520A8;
}
extern "C" CRef *RefOpForEach(CRef *pretRef, int carg, CRef *aref, CFrame *pframe)
{
    if (aref[1].m_tagk == TAGK_Pair) {
        PairHandle call;
        CRef *prefCallee;
        CRef *prefArg;
        func_00121578(&call, &prefCallee, &prefArg);
        *prefCallee = aref[0];
        for (CPair *element = (CPair *)aref[1].m_tag.m_n; element; ) {
            *prefArg = element->ref;
            CRef refIgnored = RefEval(call.p, pframe);
            element = element->next;
        }
        CPair *held = call.p;
        if (held) {
            if (--held->cref == 0) {
                CPairPtr_Destructor(&held->next, 2);
                held->ref.Decref();
                UnlinkPairNode(held);
                FreeSlotheapPv(&B_004520A8, held);
            }
        }
    }
    pretRef->SetTag(TAGK_Void);
    return pretRef;
}
