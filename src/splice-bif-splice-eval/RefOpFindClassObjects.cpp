// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CFrame;
struct SW;
extern SW B_003DD490;
extern "C" {
int CploFindSwObjectsByClass(SW *, int, int, int, int, int *);
CRef RefFromAplo(int, int *);
}
extern "C" CRef RefOpFindClassObjects(int carg, CRef *aref, CFrame *pframe)
{
    CRef refResult;
    refResult.m_tagk = TAGK_Nil;
    int grffso = (aref[1].m_tag.m_n != 0) ? 0x401 : 0x405;
    int aplo[0x180];
    int cplo = CploFindSwObjectsByClass(&B_003DD490, grffso, aref[0].m_tag.m_n, aref[1].m_tag.m_n, 0x180, aplo);
    {
        CRef refList = RefFromAplo(cplo, aplo);
        refResult = refList;
    }
    return refResult;
}
