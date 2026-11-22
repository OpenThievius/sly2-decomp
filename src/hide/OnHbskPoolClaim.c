/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "hbsk.h"

void func_001CB518(struct HBSK *phbsk); /* extern */

void OnHbskPoolClaim(struct HBSK *phbsk) {
    func_001CB518(phbsk);
    phbsk->hbsks = 0;
}
