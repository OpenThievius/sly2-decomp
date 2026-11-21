#include "sly2.h"
#include "cref.h"
CRef *CRef_SetBifk(CRef *pref, int bifk)
{
    pref->Decref();
    pref->m_tag.m_bifk = bifk;
    pref->m_tagk = TAGK_Bifk;
    return pref;
}
