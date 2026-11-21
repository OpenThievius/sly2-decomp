// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
extern "C" CRef *CRef_ConstructProc(CRef *pref, int *pshared)
{
    pref->m_tag.m_pproc = (CProc *)pshared;
    pref->m_tagk = TAGK_Proc;
    (*pshared)++;
    return pref;
}
