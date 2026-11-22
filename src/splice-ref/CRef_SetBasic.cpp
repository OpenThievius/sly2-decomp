// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
#include "cref.h"

CRef &CRef::SetBasic(BASIC *pbasic)
{
    if (pbasic != 0) {
        pbasic->OnAdd();
    }
    Decref();
    m_tag.m_pbasic = pbasic;
    m_tagk = TAGK_Basic;
    return *this;
}
