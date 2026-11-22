// SPDX-License-Identifier: GPL-3.0-or-later
#include "crefboxes.h"

extern SLOTHEAP B_00452188;

extern "C" CRef *CRef_SetVectorPtr(CRef *pref, VECTOR *pvector)
{
    pref->Decref();
    pref->m_tagk = TAGK_Vector;
    VECTORBOX *pbox = (VECTORBOX *)PvAllocSlotheapImpl(&B_00452188);
    pbox->cref = 0;
    pref->m_tag.m_pvector = &pbox->vector;
    pbox->cref = pbox->cref + 1;
    *pref->m_tag.m_pvector = *pvector;
    return pref;
}
