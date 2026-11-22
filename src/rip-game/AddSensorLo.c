/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "guard.h"

struct SENSORENTRY *PentryFindSensorLo(struct SENSOR *psensor, struct LO *plo);
void SetSensorEntryState(struct SENSOR *psensor, struct SENSORENTRY *pentry, s32 state);

void AddSensorLo(struct SENSOR *sensor, struct LO *plo) {
    struct SENSORENTRY *entry;
    u32 centry;

    if (PentryFindSensorLo(sensor, plo) == 0) {
        centry = sensor->centry;
        if (centry < 8U) {
            sensor->centry = centry + 1;
            entry = &sensor->aentry[centry];
            entry->plo = plo;
            SetSensorEntryState(sensor, entry, 0);
        }
    }
}
