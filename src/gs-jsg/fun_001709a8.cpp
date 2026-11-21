// SPDX-License-Identifier: GPL-3.0-or-later
#include "lo.h"
extern "C" int FIsBasicDerivedFrom(BASIC *, int);
extern "C" int func_001709A8(BASIC *pbasic)
{
    if (FIsBasicDerivedFrom(pbasic, 0xD) == 0) {
        return (FIsBasicDerivedFrom(pbasic, 0xB) == 0) ? -1 : 1;
    }
    return 0;
}
