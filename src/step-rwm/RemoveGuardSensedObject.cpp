// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" {
void CopyAb__FPvT0Ui(void *, void *, unsigned int);
SENSORENTRY *PentryFindSensorLo(SENSOR *, LO *);
void RemoveGuardSensedObject(STEPGUARD *guard, LO *plo) {
    SENSORENTRY *entry = PentryFindSensorLo(guard->psensor, plo);
    SENSOR *sensor = guard->psensor;
    int count = sensor->centry;
    SENSORENTRY *limit = &sensor->aentry[count - guard->csensed];
    if ((entry != 0) && (entry < limit)) {
        sensor->centry = count - 1;
        CopyAb__FPvT0Ui(entry, entry + 1, (guard->psensor->centry - (entry - sensor->aentry)) * 0x10);
    }
}
}
