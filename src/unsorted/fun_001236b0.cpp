// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
inline CRef *SetIntRef(CRef *pref, int value)
{
    pref->m_tagk = TAGK_S32;
    pref->m_tag.m_n = value;
    return pref;
}
extern "C" CRef *func_001236B0(CRef *pref, int carg, CRef *aref, void *pframe)
{
    return SetIntRef(pref, (int)(aref[0].m_tag.m_g + 0.5f));
}
