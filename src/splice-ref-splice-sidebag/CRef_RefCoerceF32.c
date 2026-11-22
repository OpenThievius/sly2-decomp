/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cref.h"

void CRef_CopyConstruct(); /* extern */

CRef *CRef_RefCoerceF32(CRef *result, CRef *source) {
    if (source->m_tagk == TAGK_F32) {
        CRef_CopyConstruct();
    } else {
        result->m_tag.m_g = (f32) source->m_tag.m_n;
        result->m_tagk = TAGK_F32;
    }
    return result;
}
