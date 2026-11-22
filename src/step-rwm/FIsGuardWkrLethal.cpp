// SPDX-License-Identifier: GPL-3.0-or-later
#include "wkr.h"
#include "stepguard.h"
extern "C" {
int FIsGuardWkrLethal(STEPGUARD *self, WKR *wkr) {
    if (-wkr->damage < self->field_0x338) return 0;
    switch (wkr->grftak) {
    case 0: case 1: case 0x80000: case 0x100000:
        return 0;
    }
    return 1;
}
}
