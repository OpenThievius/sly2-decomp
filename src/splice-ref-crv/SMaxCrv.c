/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crv.h"

f32 SMaxCrv(struct CRV *crv) {
    return crv->as[crv->ccv - 1];
}
