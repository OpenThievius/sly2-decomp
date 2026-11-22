// SPDX-License-Identifier: GPL-3.0-or-later
#include "mount.h"
extern "C" {
void Mount_SetState(MOUNT *pmount, int newState);
void OnPoActive(PO *ppo, int fActive);
void Mount_OnPoActive(MOUNT *pmount, int fActive) {
    OnPoActive(pmount, fActive);
    if (fActive != 0) {
        Mount_SetState(pmount, 1);
    } else if ((u32)(pmount->grfo >> 0x3C) & 1) {
        Mount_SetState(pmount, 0);
    }
}
}
