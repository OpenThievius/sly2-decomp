// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"

extern "C" {
void InitDprize(DPRIZE *);

// InitDprizeKey
void func_001C6AB8(DPRIZEKEY *pkey) {
    InitDprize(pkey);
    pkey->field_0x1D8 = 35.0f;
    pkey->field_0x1DC = 35.0f;
    pkey->field_0x1E4 = 0.6f;
    pkey->field_0x1D0 = 500.0f;
    pkey->field_0x1D4 = 250.0f;
    pkey->field_0x1E0 = 0.6f;
    pkey->field_0x1A0 = 0.75f;
}

}
