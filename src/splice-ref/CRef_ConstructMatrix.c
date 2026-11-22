/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crefboxes.h"

extern struct SLOTHEAP B_004521A0;

CRef *CRef_ConstructMatrix(CRef *pref, struct MATRIX4 *pmatrix) {
    struct MATRIXBOX *pbox;

    pref->m_tagk = TAGK_Matrix;
    pbox = PvAllocSlotheapImpl(&B_004521A0);
    pbox->cref = 0;
    pref->m_tag.m_pmatrix = &pbox->matrix;
    pbox->cref = pbox->cref + 1;
    *pref->m_tag.m_pmatrix = *pmatrix;
    return pref;
}
