// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "cref.h"

extern "C" CRef *CRef_ConstructBasic(CRef *pref, BASIC *pbasic)
{
    if (pbasic != 0) {
        pbasic->OnAdd();
    }
    pref->m_tag.m_pbasic = pbasic;
    pref->m_tagk = TAGK_Basic;
    return pref;
}
