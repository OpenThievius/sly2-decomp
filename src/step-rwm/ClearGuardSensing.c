/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardview.h"

void ClearGuardClassFilters(struct STEPGUARDVIEW *);
void ClearGuardIgnoredClasses(struct STEPGUARDVIEW *);

void ClearGuardSensing(struct STEPGUARDVIEW *pguard) {
    pguard->psensor->centry = 0;
    pguard->cgroup = 0;
    pguard->csensed = 0;
    ClearGuardIgnoredClasses(pguard);
    ClearGuardClassFilters(pguard);
}
