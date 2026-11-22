// SPDX-License-Identifier: GPL-3.0-or-later
#include "spire.h"
extern "C" void InitXfm_thunk(SPIRE *);
void InitSpire(SPIRE *pspire)
{
    InitXfm_thunk(pspire);
    pspire->dzMax = 3.402823466e+38f;
}
