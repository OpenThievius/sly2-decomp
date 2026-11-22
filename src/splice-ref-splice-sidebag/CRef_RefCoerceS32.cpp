// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
extern "C" {
void CRef_CopyConstruct();
CRef *CRef_RefCoerceS32(CRef *result, CRef *source) {
    if (source->m_tagk == TAGK_S32) {
        CRef_CopyConstruct();
    } else {
        s32 value = (s32) source->m_tag.m_g;
        result->m_tagk = TAGK_S32;
        result->m_tag.m_n = value;
    }
    return result;
}
}
