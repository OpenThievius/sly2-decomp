/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "crv.h"

f32 UMaxCrv(struct CRV *crv) {
    return crv->au[crv->ccv - 1];
}
