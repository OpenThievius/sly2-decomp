#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" {
void CRef_SetS32(CRef *, int);
void CRef_SetF32(CRef *, float);
}
extern "C" CRef RefOpAbs(int carg, CRef *aref, CFrame *pframe)
{
    CRef refAbs;
    refAbs.m_tagk = TAGK_Nil;
    if (aref[0].m_tagk == TAGK_S32) {
        CRef_SetS32(&refAbs, aref[0].m_tag.m_n < 0 ? -aref[0].m_tag.m_n : aref[0].m_tag.m_n);
    } else {
        float gAbs = aref[0].m_tag.m_g;
        if (gAbs < 0.0f) {
            gAbs = -gAbs;
        }
        CRef_SetF32(&refAbs, gAbs);
    }
    return refAbs;
}
