/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "spire.h"

void AddLoHierarchy(struct SPIRE *pspire);
void AppendDlEntry(struct DL *, struct SPIRE *);
extern struct DL B_003E142C;

void Spire_AddLoHierarchy(struct SPIRE *pspire) {
    AddLoHierarchy(pspire);
    AppendDlEntry(&B_003E142C, pspire);
}
