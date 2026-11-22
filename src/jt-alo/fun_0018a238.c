// SPDX-License-Identifier: GPL-3.0-or-later
#include "slyview.h"

void RenderJt(struct SLYVIEW *self);
void func_00190D10(void);

void func_0018A238(struct SLYVIEW *self) {
    if (self->jts == 3) {
        func_00190D10();
    }
    RenderJt(self);
}
