#include "sly2.h"
#include "cref.h"
struct CFrame;
struct CLQ;
extern "C" void CRef_RefCoerceF32(CRef *, CRef *);
void FitClq__FffffP3CLQ(float, float, float, float, CLQ *);
extern "C" CRef RefOpClqFit(int carg, CRef *aref, CFrame *pframe)
{
    CRef refClq;
    refClq.SetTag(TAGK_Clq);
    {
        CRef refG0;
        CRef refG1;
        CRef refG2;
        CRef refG3;
        CRef_RefCoerceF32(&refG0, &aref[0]);
        float g0 = refG0.m_tag.m_g;
        CRef_RefCoerceF32(&refG1, &aref[1]);
        float g1 = refG1.m_tag.m_g;
        CRef_RefCoerceF32(&refG2, &aref[2]);
        float g2 = refG2.m_tag.m_g;
        CRef_RefCoerceF32(&refG3, &aref[3]);
        FitClq__FffffP3CLQ(g0, g1, g2, refG3.m_tag.m_g, refClq.m_tag.m_pclq);
    }
    return refClq;
}
