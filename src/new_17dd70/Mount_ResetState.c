/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mount.h"

s32 FIsPoSwFocus(struct MOUNT *pmount);
void Mount_SetState(struct MOUNT *pmount, s32 newState);
void Mount_UpdateHealthBlot(struct MOUNT *pmount);
void func_0017F6B0(struct MOUNT *pmount);

void Mount_ResetState(struct MOUNT *pmount) {
    func_0017F6B0(pmount);
    if (FIsPoSwFocus(pmount) != 0) {
        Mount_SetState(pmount, 1);
    } else {
        Mount_SetState(pmount, 0);
    }
    Mount_UpdateHealthBlot(pmount);
}
