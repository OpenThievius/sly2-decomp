// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"

extern "C" {
void RetractAsega(ASEGA *);

void RetractAsegaHandle(ASEGA **ppasega)
{
    if (*ppasega != 0) {
        RetractAsega(*ppasega);
        (*ppasega)->Slot2();
        *ppasega = 0;
    }
}
}
