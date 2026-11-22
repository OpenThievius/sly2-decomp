/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "suv.h"

void CloneXfm(struct SUV *suv, struct SUV *suvSource); /* extern */

void CloneSuv(struct SUV *suv, struct SUV *suvSource) {
    s32 *pcshare;

    CloneXfm(suv, suvSource);
    pcshare = suv->pcshare;
    *pcshare += 1;
}
