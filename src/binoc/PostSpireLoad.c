/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "spire.h"

enum TNS { TNS_X };

void PostLoLoad(struct SPIRE *pspire);
void SetTnTns__FP2TN3TNS(struct TN *ptn, enum TNS tns);

void PostSpireLoad(struct SPIRE *pspire) {
    struct TN *ptn;

    PostLoLoad(pspire);
    ptn = pspire->ptn;
    if (ptn != 0) {
        SetTnTns__FP2TN3TNS(ptn, TNS_X);
    }
}
