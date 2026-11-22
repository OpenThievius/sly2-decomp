// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "guard.h"
extern "C" {
SENSORENTRY *PentryFindSensorLo(SENSOR *, LO *);
void SetSensorEntryState(SENSOR *, SENSORENTRY *, s32);
void memmove(void *, void *, s32);

void RemoveSensorLo(SENSOR *sensor, LO *plo) {
    SENSORENTRY *entry = PentryFindSensorLo(sensor, plo);
    if (entry != 0) {
        SetSensorEntryState(sensor, entry, 0);
        sensor->centry = sensor->centry - 1;
        memmove(entry, entry + 1, (sensor->aentry + sensor->centry - entry) * sizeof(SENSORENTRY));
    }
}

}
