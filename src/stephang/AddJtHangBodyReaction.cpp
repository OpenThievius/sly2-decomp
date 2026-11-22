// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
extern "C" {
void AddSoAcceleration(SO *, QW);
void AddSoAngularAcceleration(SO *, QW);

void AddJtHangBodyReaction(SLY *sly) {
    AddSoAcceleration(sly->phangbody->pso, sly->accelHang);
    AddSoAngularAcceleration(sly->phangbody->pso, sly->accelAngularHang);
}

}
