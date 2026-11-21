#include "sly2.h"
#include "cref.h"
extern "C" {
CRef *CRef_SetMethod(CRef *pref, int *pm)
{
    ++*pm;
    pref->Decref();
    pref->m_tag.m_pmethod = (CMethod *)pm;
    pref->m_tagk = TAGK_Method;
    return pref;
}
}
