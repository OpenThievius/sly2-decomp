/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cref.h"

void CRef_AddRef(CRef *pref);
void CRef_Destruct(CRef *pref);

CRef *__as__4CRefRC4CRef(CRef *pref, CRef *prefSource) {
    CRef_AddRef(prefSource);
    CRef_Destruct(pref);
    pref->m_tagk = prefSource->m_tagk;
    pref->m_tag.m_n = prefSource->m_tag.m_n;
    return pref;
}
