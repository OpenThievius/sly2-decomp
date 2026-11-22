/* SPDX-License-Identifier: GPL-3.0-or-later */
/* BYTES8, eight bytes copied as one block whose type is not known: AttachCrv_Clone, AttachCyl_Clone and AttachFlat_Clone keep them across
   the base clone (pzo_hide.h), AddVehicleWheel copies a script's eight bytes into VEHICLEWHEEL (vehicle.h). C and C++. */
#ifndef SLY2_BYTES8_H
#define SLY2_BYTES8_H
#include "types.h"

struct BYTES8 {
    u8 bytes[8];
};
#endif
