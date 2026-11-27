// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
extern "C" {
int PloNew(int, STEPGUARD *, int, int);

int func_0020A9C0(STEPGUARD *self) {
    int plo;
    if (self->caoid == 0) {
        plo = PloNew(0x78, self, 0x2CC, -1);
        self->afound[self->cfound++] = plo;
        self->aoid[self->caoid++] = 0x2CC;
    } else {
        plo = self->afound[0];
    }
    return plo;
}
}
