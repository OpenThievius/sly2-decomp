// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
void AddGuardAimOid(STEPGUARD *owner, int oid)
{
    if (oid != -1) {
        unsigned count = owner->caoid;
        if (count < 8) {
            owner->aoid[count] = oid;
            owner->caoid = count + 1;
        }
    }
}
