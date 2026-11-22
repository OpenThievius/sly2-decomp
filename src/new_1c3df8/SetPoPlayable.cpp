/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "po.h"
#include "sw.h"
extern "C" SW B_003DD490;
extern "C" void *__builtin_new(unsigned int);
extern "C" int GetPoVjoyMode(PO *);
extern "C" void *VJOY_constructor(void *, PO *);
extern "C" void SetVjoyMode(void *, int);
extern "C" void SetSwFocusBase(SW *, PO *);
extern "C" void SetPoPlayable(PO *ppo, int vjoym)
{
    if (vjoym == GetPoVjoyMode(ppo))
        return;
    if (ppo->pjoy == 0) {
        unsigned cpo = B_003DD490.clo;
        if (cpo >= 16)
            return;
        B_003DD490.aplo[cpo] = ppo;
        B_003DD490.clo = cpo + 1;
        ppo->pjoy = (JOY *)VJOY_constructor(__builtin_new(0xE0), ppo);
    }
    if (vjoym >= -1) {
        if (vjoym > 0) {
            if (vjoym == 1 && ppo != B_003DD490.ppoFocusBase) {
                PO *ppoFocus = B_003DD490.ppoFocusBase;
                if (ppoFocus != 0)
                    ppoFocus->SetPlayable(0);
                SetSwFocusBase(&B_003DD490, ppo);
            }
        } else {
            if (ppo == B_003DD490.ppoFocusBase)
                SetSwFocusBase(&B_003DD490, 0);
        }
    }
    SetVjoyMode(ppo->pjoy, vjoym);
}
