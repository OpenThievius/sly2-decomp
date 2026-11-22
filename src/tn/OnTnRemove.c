/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "tn.h"

void RemoveAloHierarchy(struct TN *tn);             /* extern */
void SetTnTns__FP2TN3TNS(struct TN *tn, enum TNS tns); /* extern */

void OnTnRemove(struct TN *tn) {
    RemoveAloHierarchy(tn);
    SetTnTns__FP2TN3TNS(tn, TNS_OFF);
}
