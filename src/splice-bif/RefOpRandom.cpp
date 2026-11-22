#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" {
CRef CRef_RefCoerceF32(CRef *pref);
int NRandInRange(int, int);
float GRandInRange(float, float);
void SetF32__4CReff(CRef *, float);
}
extern "C" CRef RefOpRandom(int carg, CRef *aref, CFrame *pframe)
{
    CRef refRandom;
    refRandom.m_tagk = TAGK_Nil;
    if (aref[0].m_tagk == TAGK_S32 && aref[1].m_tagk == TAGK_S32) {
        refRandom.SetS32(NRandInRange(aref[0].m_tag.m_n, aref[1].m_tag.m_n));
    } else {
        float gMin = CRef_RefCoerceF32(&aref[0]).m_tag.m_g;
        float gMax = CRef_RefCoerceF32(&aref[1]).m_tag.m_g;
        SetF32__4CReff(&refRandom, GRandInRange(gMin, gMax));
    }
    return refRandom;
}
