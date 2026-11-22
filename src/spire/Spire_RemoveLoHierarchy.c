/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "spire.h"

void RemoveLoHierarchy(struct SPIRE *pspire);
void RemoveDlEntry(struct DL *, struct SPIRE *);
extern struct DL B_003E142C;

void Spire_RemoveLoHierarchy(struct SPIRE *pspire) {
    RemoveLoHierarchy(pspire);
    RemoveDlEntry(&B_003E142C, pspire);
}
