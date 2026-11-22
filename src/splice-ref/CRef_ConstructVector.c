/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crefboxes.h"

extern struct SLOTHEAP B_00452188;

CRef *CRef_ConstructVector(CRef *pref, struct VECTOR *pvector) {
    struct VECTORBOX *pbox;

    pref->m_tagk = TAGK_Vector;
    pbox = PvAllocSlotheapImpl(&B_00452188);
    pbox->cref = 0;
    pref->m_tag.m_pvector = &pbox->vector;
    pbox->cref = pbox->cref + 1;
    *pref->m_tag.m_pvector = *pvector;
    return pref;
}
