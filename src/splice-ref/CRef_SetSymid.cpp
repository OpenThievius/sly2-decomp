#include "types.h"
#include "cref.h"
extern "C" void CRef_Destruct(CRef *pref);

int CRef_SetSymid(CRef *pref, int symid)
{
    CRef_Destruct(pref);
    pref->m_tag.m_n = symid;
    pref->m_tagk = TAGK_Symid;
    return (sptr)pref;
}
