// SPDX-License-Identifier: GPL-3.0-or-later
#include "guardview.h"

QW ConvertAloPos(struct STEPVIEW *paloFrom, struct STEPVIEW *paloTo, QW pos);
void TranslateSoToPos();                            /* extern */

void TranslateStepToPos(struct STEPVIEW *pstep) {
    TranslateSoToPos();
    pstep->posWorld = ConvertAloPos(pstep, 0, pstep->posLocal);
}
