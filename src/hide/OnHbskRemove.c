/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "hbsk.h"

void RemoveDlEntry(struct DL *pdl, struct HBSK *phbsk); /* extern */
void func_001F3E00(struct HBSK *phbsk);                 /* extern */
extern struct DL B_003E13E4;

void OnHbskRemove(struct HBSK *phbsk) {
    func_001F3E00(phbsk);
    RemoveDlEntry(&B_003E13E4, phbsk);
}
