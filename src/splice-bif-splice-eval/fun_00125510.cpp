// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
struct CFrame {
    char pad0[8];
    int cpframeParent;
    CFrame *pframeParent;
    char pad1[0x14];
    int unk0x24;
    CRef *PrefFindBinding(unsigned, int);
};
extern "C" CRef func_00125510(int carg, CRef *aref, CFrame *pframe)
{
    if (pframe != 0 && pframe->cpframeParent == 1) {
        CFrame *pframeCur = pframe;
        while (pframeCur->unk0x24 == 0) {
            pframeCur = pframeCur->pframeParent;
            if (pframeCur == 0 || pframeCur->cpframeParent != 1)
                goto fail;
        }
        CRef *pref = pframeCur->pframeParent->PrefFindBinding(aref[0].m_tag.m_n, 1);
        if (pref != 0)
            return *pref;
    }
fail:
    return CRef(0x86, TAGK_Bifk);
}
