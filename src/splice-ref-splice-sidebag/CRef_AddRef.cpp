#include "lo.h"
#include "cref.h"
extern "C" void CRef_AddRef(CRef *pref)
{
    switch (pref->m_tagk) {
    case TAGK_Matrix:
        ((int *)pref->m_tag.m_pbasic)[0x10]++;
        break;
    case TAGK_Vector:
    case TAGK_Clq:
        ((int *)pref->m_tag.m_pbasic)[4]++;
        break;
    case TAGK_Lm:
        ((int *)pref->m_tag.m_pbasic)[2]++;
        break;
    case TAGK_Smp:
        ((int *)pref->m_tag.m_pbasic)[3]++;
        break;
    case TAGK_Basic: {
        BASIC *pbasic = pref->m_tag.m_pbasic;
        if (pbasic != 0)
            pbasic->OnAdd();
        break;
    }
    case TAGK_Pair:
    case TAGK_Proc:
    case TAGK_Method:
        ((int *)pref->m_tag.m_pbasic)[0]++;
        break;
    }
}
