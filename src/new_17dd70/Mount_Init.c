/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "mount.h"

void func_0017F090(struct MOUNT *pmount);
void func_0017F3E0(void *pobject, s32 centry, struct ANIMENTRY *aentry);
extern struct MOUNT *g_2dfb80;

void Mount_Init(struct MOUNT *pmount) {
    func_0017F090(pmount);
    func_0017F3E0(pmount, 5, pmount->aentry);
    pmount->state = -1;
    g_2dfb80 = pmount;
    pmount->field_0x2A8 = -1;
}
