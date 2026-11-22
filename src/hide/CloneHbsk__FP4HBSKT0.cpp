// SPDX-License-Identifier: GPL-3.0-or-later
#include "hbsk.h"
extern "C" {
void CSo_Clone(HBSK *phbsk, HBSK *phbskSource);
void CloneHbsk__FP4HBSKT0(HBSK *phbsk, HBSK *phbskSource) {
    DLE dle = phbsk->dle;
    CSo_Clone(phbsk, phbskSource);
    phbsk->dle = dle;
}
}
