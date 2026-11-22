// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"

extern "C" CRef *bevy_splice_value_list_ref(CRef *pref, int *pshared)
{
    (*pshared)++;
    pref->Decref();
    pref->m_tag.m_ppair = (CPair *)pshared;
    pref->m_tagk = TAGK_Pair;
    return pref;
}
