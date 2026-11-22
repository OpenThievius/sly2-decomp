// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct STEPGUARD;

void AddGuardAimOid(struct STEPGUARD *pguard, s32 oid);
void ResolveGuardAimObjects(struct STEPGUARD *pguard);

void AddGuardAimOidResolve(struct STEPGUARD *pguard, s32 oid) {
    AddGuardAimOid(pguard, oid);
    ResolveGuardAimObjects(pguard);
}
