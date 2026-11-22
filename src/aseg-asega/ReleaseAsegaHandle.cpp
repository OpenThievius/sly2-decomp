// SPDX-License-Identifier: GPL-3.0-or-later
#include "asega.h"

extern "C" void ReleaseAsegaHandle(ASEGA **ppasega)
{
    ASEGA *pasega = *ppasega;
    if (pasega != 0) {
        pasega->Slot2();
        *ppasega = 0;
    }
}
