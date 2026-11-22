// SPDX-License-Identifier: GPL-3.0-or-later
#include "po.h"
#include "sw.h"
extern "C" PO *PpoSwFocus(SW *);

void SetSwFocusOverride(SW *psw, PO *ppo)
{
    PO *ppoOld = PpoSwFocus(psw);
    PO *ppoNew = ppo;
    if (ppoNew == 0)
        ppoNew = psw->ppoFocusBase;
    if (ppoOld != ppoNew && ppoOld != 0)
        ppoOld->OnActive(0);
    psw->ppoFocusOverride = ppo;
    if (ppoOld != ppoNew && ppoNew != 0)
        ppoNew->OnActive(1);
}
