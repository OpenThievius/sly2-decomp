// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" CRef CRef_RefCoerceF32(CRef *pref);
extern "C" CRef RefOpLm(int carg, CRef *aref, CFrame *pframe)
{
    CRef ref;
    ref.SetTag(TAGK_Lm);
    float *pvec = (float *)ref.m_tag.m_plm;
    for (int index = 0; index < 2; index++) {
        pvec[index] = CRef_RefCoerceF32(&aref[index]).m_tag.m_g;
    }
    return ref;
}
