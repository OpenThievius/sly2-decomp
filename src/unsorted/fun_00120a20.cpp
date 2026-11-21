// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CFrame;
extern "C" CRef func_00120A20(int carg, CRef *aref, CFrame *pframe)
{
    return CRef(TAGK_Bool, aref->m_tagk == 0x20 || aref->m_tagk == 0x19);
}
