/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "hbsk.h"

void AppendDlEntry(struct DL *pdl, struct HBSK *phbsk); /* extern */
void func_001F3EA8(struct HBSK *phbsk);                 /* extern */
extern struct DL B_003E13E4;

void OnHbskAdd(struct HBSK *phbsk) {
    func_001F3EA8(phbsk);
    AppendDlEntry(&B_003E13E4, phbsk);
}
