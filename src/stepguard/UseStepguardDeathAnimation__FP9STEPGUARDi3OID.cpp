// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "mount.h"
enum OID { OID_NONE = -1 };
void UseStepguardDeathAnimation(MOUNT *pmount, int a, OID oid);
void UseStepguardDeathAnimation(MOUNT *pmount, int a, OID oid)
{
    unsigned n = pmount->crec;
    if (n < 4) {
        pmount->crec = n + 1;
        MOUNTREC *prec = &pmount->arec[n];
        prec->oidPart = a;
        prec->oidObject = oid;
    }
}
