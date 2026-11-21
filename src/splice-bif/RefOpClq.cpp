// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" CRef CRef_RefCoerceF32(CRef *pref);
extern "C" CRef RefOpClq(int carg, CRef *aref, CFrame *pframe)
{
    CRef ref;
    ref.SetTag(TAGK_Clq);
    float *pvec = (float *)ref.m_tag.m_pclq;
    for (int index = 0; index < 3; index++) {
        pvec[index] = CRef_RefCoerceF32(&aref[index]).m_tag.m_g;
    }
    return ref;
}
