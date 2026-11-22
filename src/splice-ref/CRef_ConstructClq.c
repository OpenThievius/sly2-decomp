/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crefboxes.h"

extern struct SLOTHEAP B_004521B8;

CRef *CRef_ConstructClq(CRef *pref, struct CLQ *pclq) {
    struct CLQBOX *pbox;

    pref->m_tagk = TAGK_Clq;
    pbox = PvAllocSlotheapImpl(&B_004521B8);
    pbox->cref = 0;
    pref->m_tag.m_pclq = &pbox->clq;
    pbox->cref = pbox->cref + 1;
    *pref->m_tag.m_pclq = *pclq;
    return pref;
}
