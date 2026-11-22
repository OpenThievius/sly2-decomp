// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "so.h"
extern "C" {
void CloneStep(STEPGUARD *, STEPGUARD *);
void func_00209770(GUARDHEADING *, STEPGUARD *);
void CloneGuardAnimrefs(STEPGUARD *);
void CloneGuard(STEPGUARD *pguard, STEPGUARD *psource) {
    SENSOR *psensor = pguard->psensor;
    CloneStep(pguard, psource);
    func_00209770(&pguard->heading, pguard);
    pguard->psensor = psensor;
    psensor->Slot41((SO *)psource->psensor);
    CloneGuardAnimrefs(pguard);
}
}
