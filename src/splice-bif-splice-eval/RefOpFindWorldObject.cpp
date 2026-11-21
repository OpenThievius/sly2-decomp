// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
extern "C" {
extern char B_003DD490[];
}

extern "C" CRef RefOpFindWorldObject()
{
    CRef refTemp;
    refTemp.m_tagk = TAGK_Nil;
    refTemp.SetBasic((BASIC *)B_003DD490);
    return refTemp;
}
