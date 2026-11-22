// SPDX-License-Identifier: GPL-3.0-or-later
#include "timedcall.h"
struct CFrame;
extern "C" void PairHandle_Assign(CPair **, CPair *);
extern "C" CRef *RefOpSetCarOrCdr(CRef *pref, int carg, CRef *aref, CFrame *pframe, int tagkSet) {
    CPair *ppair = aref[0].m_tag.m_ppair;
    if (tagkSet == 0x23) {
        ppair->ref = aref[1];
    } else if (aref[1].m_tagk == TAGK_Pair) {
        PairHandle_Assign(&ppair->next, aref[1].m_tag.m_ppair);
    } else {
        PairHandle_Assign(&ppair->next, 0);
    }
    pref->SetTag(TAGK_Void);
    return pref;
}
