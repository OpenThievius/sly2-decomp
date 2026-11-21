// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
extern "C" CRef *CRef_ConstructPair(CRef *pref, int *pshared)
{
    pref->m_tag.m_ppair = (CPair *)pshared;
    pref->m_tagk = TAGK_Pair;
    (*pshared)++;
    return pref;
}
