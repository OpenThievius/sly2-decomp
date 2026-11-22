// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"

CRef &CRef::SetF32(f32 g)
{
    Decref();
    m_tag.m_g = g;
    m_tagk = TAGK_F32;
    return *this;
}
