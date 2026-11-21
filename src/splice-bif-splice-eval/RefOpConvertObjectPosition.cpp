#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" {
QW ConvertAloPos(int, int, QW);
void CRef_ConstructVectorValue(CRef *, QW);
}
extern "C" CRef RefOpConvertObjectPosition(int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    CRef_ConstructVectorValue(&refResult, ConvertAloPos(aref[0].m_tag.m_n, aref[1].m_tag.m_n, *(QW *)aref[2].m_tag.m_pvector));
    return refResult;
}
