// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"

extern "C" {
void func_001CB5D0(DPRIZE *pdprize, void *pv);

void func_001C7EA8(DPRIZE *pdprize, void *pv) {
    func_001CB5D0(pdprize, pv);
    pdprize->SetDprizes(-1);
}
}
