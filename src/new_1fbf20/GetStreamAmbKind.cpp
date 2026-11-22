// SPDX-License-Identifier: GPL-3.0-or-later
#include "streamamb.h"

int GetStreamAmbKind(STREAMAMB *pamb) {
    int kind = 1;
    int result = 2;
    int grfStart = pamb->grfStart & 4;
    if (grfStart == 0) {
        result = kind;
    }
    return result;
}
