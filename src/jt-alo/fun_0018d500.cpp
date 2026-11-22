// SPDX-License-Identifier: GPL-3.0-or-later
#include "jt.h"

extern "C" int FActiveCplcy(void *);
extern char B_002DE2E0[];

int func_0018D500(JT *pjt)
{
    int result = 1;
    if (pjt->binocState == 1) {
        return 0;
    } else {
        if (FActiveCplcy(B_002DE2E0)) {
            result = 0;
        }
        return result;
    }
}
