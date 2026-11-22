/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "tn.h"

void CloneXfm(struct TN *tn, struct TN *tnSource);  /* extern */
struct CRV *PloCloneLo(struct CRV *pcrv, struct SO *psoParent); /* extern */

void CloneTn(struct TN *tn, struct TN *tnSource) {
    CloneXfm(tn, tnSource);
    tn->pcrv = PloCloneLo(tn->pcrv, tn->psoParent);
}
