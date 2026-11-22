// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
extern "C" {
QW PosLoWorld(void *);
void ProjectSoTransform(SO *);

void ProjectJtTransform(SLY *self) {
    QW partPosition;

    partPosition = PosLoWorld(self->apartHide[1]);
    self->cbounds = 0;
    self->abounds[1] = partPosition;
    ProjectSoTransform(self);
    if (self->jtcs == 0) {
        self->abounds[0] = PosLoWorld(self);
        self->abounds[2] = PosLoWorld(self->apartHide[1]);
        self->cbounds = 3;
    } else {
        self->cbounds = 0;
    }
}

}
