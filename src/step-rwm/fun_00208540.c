/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void AddAlertGuard(struct ALERT *, struct STEPGUARDVIEW *);
struct ALERT *PalertEnsure(struct BASIC *);
void RemoveAlertGuard(struct ALERT *, struct STEPGUARDVIEW *);

void func_00208540(struct STEPGUARDVIEW *pguard, struct BASIC *pbasicAlert) {
    struct BASIC *pbasicOld;
    struct ALERT *palert;

    pbasicOld = pguard->pbasicAlert;
    if (pbasicAlert != pbasicOld) {
        if (pbasicOld != 0) {
            RemoveAlertGuard(pguard->palert, pguard);
            pguard->palert = 0;
        }
        pguard->pbasicAlert = pbasicAlert;
        if (pbasicAlert != 0) {
            palert = PalertEnsure(pbasicAlert);
            pguard->palert = palert;
            AddAlertGuard(palert, pguard);
        }
    }
}
