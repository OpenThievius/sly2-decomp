#include "sly2.h"
#include "cref.h"
struct CPAIR { int pad[2]; CRef ref; CPAIR *next; };
struct CFrame;
extern "C" CRef RefOpMaximum(int carg, CRef *aref, CFrame *pframe)
{
    CRef best = aref[0];
    if (aref[1].m_tagk != 0)
        aref = (CRef *)aref[1].m_tag.m_pbasic;
    else
        aref = 0;
    CPAIR *pair = (CPAIR *)aref;
    for (; pair != 0; pair = pair->next) {
        if (best.m_tagk == 0x15) {
            if (pair->ref.m_tagk == 0x15) {
                CRef *pref = &pair->ref;
                if (best.m_tag.m_n < pref->m_tag.m_n)
                    best = *pref;
            } else {
                CRef *pref = &pair->ref;
                if ((float)best.m_tag.m_n < pref->m_tag.m_g)
                    best = *pref;
            }
        } else {
            if (pair->ref.m_tagk == 0x15) {
                CRef *pref = &pair->ref;
                if (best.m_tag.m_g < (float)pref->m_tag.m_n)
                    best = *pref;
            } else {
                CRef *pref = &pair->ref;
                if (best.m_tag.m_g < pref->m_tag.m_g)
                    best = *pref;
            }
        }
    }
    return best;
}
