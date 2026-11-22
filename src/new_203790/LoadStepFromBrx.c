// SPDX-License-Identifier: GPL-3.0-or-later
#include "guardview.h"
#include "sly2.h"

QW ConvertAloPos(struct SO *paloFrom, struct STEPVIEW *paloTo, QW pos);
void LoadPoFromBrx();                               /* extern */
f32 *func_001F8300(struct STEPVIEW *pstep);
extern QW g_2a2dd0;

void LoadStepFromBrx(struct STEPVIEW *pstep) {
    LoadPoFromBrx();
    pstep->posLocal = ConvertAloPos(pstep->psoParent, pstep, g_2a2dd0);
    func_001F8300(pstep);
}
