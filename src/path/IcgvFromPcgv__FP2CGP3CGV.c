/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "cg.h"

s32 IcgvFromPcgv__FP2CGP3CGV(struct CG *pcg, struct CGV *pcgv) {
    return pcgv - pcg->acgv;
}
