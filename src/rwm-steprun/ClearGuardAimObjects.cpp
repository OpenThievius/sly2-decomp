// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"
#include "stepguard.h"

extern "C" void ClearGuardAimObjects(STEPGUARD *pguard) {
    pguard->caoid = 0;
    pguard->cfound = 0;
}
