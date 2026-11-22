/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct JT;
struct SAFEPT;

void WarpJtToSafePoint(struct JT *pjt, struct SAFEPT *psafept);

/* the zap part's first word is its JT (jtzap.h's JTZAP, C++ only) */
void WarpZapToSafePoint(struct JT **ppjt) {
    WarpJtToSafePoint(*ppjt, 0);
}
