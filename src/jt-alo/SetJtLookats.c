// SPDX-License-Identifier: GPL-3.0-or-later
#include "slyview.h"

void AddLookat(void *plookat);
void RemoveLookat(void *plookat);

void SetJtLookats(struct SLYVIEW *self, s32 grfLookat) {
    void *plookat;

    plookat = self->alookat[0];
    if (plookat != 0) {
        if (grfLookat & 1) {
            AddLookat(plookat);
        } else {
            RemoveLookat(plookat);
        }
        if (grfLookat & 2) {
            AddLookat(self->alookat[1]);
        } else {
            RemoveLookat(self->alookat[1]);
        }
        if (grfLookat & 4) {
            AddLookat(self->alookat[2]);
        } else {
            RemoveLookat(self->alookat[2]);
        }
        if (grfLookat & 8) {
            AddLookat(self->alookat[3]);
        } else {
            RemoveLookat(self->alookat[3]);
        }
        if (grfLookat & 0x10) {
            AddLookat(self->alookat[4]);
        } else {
            RemoveLookat(self->alookat[4]);
        }
        if (grfLookat & 0x20) {
            AddLookat(self->plookatBit5);
        } else {
            RemoveLookat(self->plookatBit5);
        }
        if (grfLookat & 0x40) {
            AddLookat(self->plookatBit6);
            return;
        }
        RemoveLookat(self->plookatBit6);
    }
}
