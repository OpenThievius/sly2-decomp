// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "po.h"
#include "sw.h"
extern "C" {
CRef func_001D8B20(const CRef &value, const char *first, ...);
PO *PpoSwFocus(SW *);
int FIsBasicDerivedFrom(PO *, int);
void UpdateSwTargetList(SW *, int, int, int);
void func_001C48C0(SW *);
extern const char RO_002A76F8[];
}
void SetSwFocusBase(SW *psw, PO *ppo)
{
    PO *ppoOld = PpoSwFocus(psw);
    PO *ppoNew = psw->ppoFocusOverride;
    if (ppoNew == 0)
        ppoNew = ppo;
    if (ppoOld != ppoNew && ppoOld != 0)
        ppoOld->OnActive(0);
    psw->ppoFocusBase = ppo;
    if (ppoOld != ppoNew && ppoNew != 0)
        ppoNew->OnActive(1);
    if (ppo != 0) {
        if (FIsBasicDerivedFrom(ppo, 0x34)) {
            func_001D8B20(CRef(ppo->oid, TAGK_S32), RO_002A76F8, 0);
        }
    }
    UpdateSwTargetList(psw, 0, 0, 0);
    func_001C48C0(psw);
}
