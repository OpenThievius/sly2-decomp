#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" CRef CRef_RefCoerceF32(CRef *);
extern "C" float g_2dded0;

CRef RefOpDeferObjectUpdate(int carg, CRef *aref, CFrame *pframe)
{
    CRef refVoid;
    refVoid.SetTag(TAGK_Void);
    float *pobject = (float *)aref[0].m_tag.m_n;
    float dt = CRef_RefCoerceF32(&aref[1]).m_tag.m_g;
    pobject[0x30 / 4] = g_2dded0 + dt;
    return refVoid;
}
