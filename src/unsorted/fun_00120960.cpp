// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" CRef func_00120960(int carg, CRef *aref, CFrame *pframe)
{
    return CRef(TAGK_Bool, aref->m_tagk == 0x1F || aref->m_tagk == 0);
}
