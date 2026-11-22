// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "guard.h"
extern "C" void InitLo(LO *);
extern "C" void ResetAnimref(ANIMREF *, STEPGUARD *);
extern "C" const float RO_FLT_002A88C8;
void func_0020AD38(AIMSTATE *self) {
    InitLo(self);
    self->field_0x50 = 0;
    self->field_0x54 = 300.0f;
    self->field_0x58 = -5000.0f;
    self->field_0x5C = 5000.0f;
    self->field_0x60 = 0.2f;
    self->field_0x64 = 0.5f;
    self->radLimit = 0.17453295f;
    self->field_0xA8 = 1;
    self->oidA = -1;
    self->oidB = -1;
    self->oidLabel = -1;
    self->field_0x6C = RO_FLT_002A88C8;
    ResetAnimref(&self->animref, self->pguard);
}
