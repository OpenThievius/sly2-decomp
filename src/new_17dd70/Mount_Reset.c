/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mount.h"

void Mount_SetState(struct MOUNT *pmount, s32 newState);
void func_0017F110(struct MOUNT *pmount);

void Mount_Reset(struct MOUNT *pmount) {
    func_0017F110(pmount);
    Mount_SetState(pmount, -1);
}
