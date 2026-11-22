// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "clock.h"
#include "guard.h"
extern "C" {

// retail walks a bare pointer to each entry's tState (aentry[0].tState = 0x108), state sits one word before it;
// the typed member form (struct member stores) lets the compiler hoist the g_2dded0.t load: best 3 words off
void ResetSensorStates(SENSOR *sensor) {
    for (s32 ientry = 0; ientry < sensor->centry; ientry++) {
        char *entryTime = (char *)&sensor->aentry[0].tState + ientry * sizeof(SENSORENTRY);
        *(s32 *)(entryTime - 4) = 0;
        *(f32 *)entryTime = g_2dded0.t;
    }
}

}
