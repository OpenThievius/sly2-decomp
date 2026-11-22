// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "asega.h"
#include "chn.h"
extern QW g_2a2dd0;
extern "C" int FAsegaGone(ASEGA *);
extern "C" CHN *PchnFindAseg(void *, void *, int, int);
extern "C" QW func_00204ED8(float t, void *plo, ASEGA *asega)
{
    QW vel = g_2a2dd0;
    if (asega) {
        if (FAsegaGone(asega))
            return vel;
        CHN *chn = PchnFindAseg(asega->paseg, plo, 6, 1);
        if (chn) {
            chn->curve->Eval(t, asega->svtLocal, 0, &vel);
        }
    }
    return vel;
}
