// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" {
CRef CRef_RefCoerceF32(CRef *);
}
extern "C" CRef *RefOpClqEvaluateLm(CRef *pret, int carg, CRef *aref, CFrame *pframe)
{
    const float *pclq = (const float *)aref[0].m_tag.m_pclq;
    const float *plm = (const float *)aref[1].m_tag.m_plm;
    CRef refT = CRef_RefCoerceF32(&aref[2]);
    float gValue = pclq[0] + refT.m_tag.m_g * (pclq[1] + refT.m_tag.m_g * pclq[2]);
    float gLo = plm[0];
    float gHi = plm[1];
    if (gValue < gLo)
        gValue = gLo;
    else if (gHi < gValue)
        gValue = gHi;
    pret->m_tag.m_g = gValue;
    pret->m_tagk = TAGK_F32;
    return pret;
}
