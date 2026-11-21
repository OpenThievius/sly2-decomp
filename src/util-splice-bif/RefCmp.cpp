#include "sly2.h"
#include "cref.h"
extern "C" CRef *RefCmp(CRef *prefReturn, const CRef *aref, int cmpk, int unused, int nUnknownResult)
{
    float agOperand[2];
    for (int iOperand = 0; iOperand < 2; ++iOperand) {
        if (aref[iOperand].m_tagk == TAGK_F32)
            agOperand[iOperand] = aref[iOperand].m_tag.m_g;
        else
            agOperand[iOperand] = (float)aref[iOperand].m_tag.m_n;
    }
    int fResult;
    switch (cmpk) {
    case 0:
        fResult = agOperand[0] < agOperand[1];
        break;
    case 1:
        fResult = agOperand[0] <= agOperand[1];
        break;
    case 2:
        fResult = agOperand[0] > agOperand[1];
        break;
    case 3:
        fResult = agOperand[0] >= agOperand[1];
        break;
    default:
        fResult = nUnknownResult;
    }
    prefReturn->m_tag.m_n = fResult;
    prefReturn->m_tagk = TAGK_Bool;
    return prefReturn;
}
