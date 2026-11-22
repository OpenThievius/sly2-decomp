// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"

extern "C" {
void func_001CB518(DPRIZE *pdprize, void *pv);

void func_001C7E68(DPRIZE *pdprize, void *pv) {
    func_001CB518(pdprize, pv);
    pdprize->SetDprizes(0);
}
}
