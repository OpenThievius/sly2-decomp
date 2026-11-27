// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "jt.h"
void SetJtLookTarget();
void SetJtLookTargetHeld(JT *self)
{
    SetJtLookTarget();
    self->fLookHold = 1;
}
