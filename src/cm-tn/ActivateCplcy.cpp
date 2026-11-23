// SPDX-License-Identifier: GPL-3.0-or-later
#include "cm.h"
extern "C" void ActivateCplcy(CPLCY *self, int value)
{
    self->active = value;
    self->savedNearClip = B_002DDF40.sNearClip;
    self->savedRadFovTarget = B_002DDF40.radFovTarget;
}
