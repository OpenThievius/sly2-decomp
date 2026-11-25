#include "cref.h"
struct CPair { int pad0; };
extern "C" void CRef_CopyConstruct(CRef *, CRef *);
extern "C" CRef *SubscribeLoStruct__FP2LOPFPv5MSGIDPv_vPv(CRef *prefReturn, int carg, CRef *aref)
{
    CRef_CopyConstruct(prefReturn, (CRef *)(aref->m_tag.m_n + 8));
    return prefReturn;
}
