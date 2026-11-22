/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "blipview.h"

void AppendDlEntry(struct DL *pdl, void *pv);
void RemoveDlEntry(struct DL *pdl, void *pv);
extern struct DL B_002DEB00;

void RemoveBlip__FP4BLIP(struct BLIPVIEW *pblip) {
    RemoveDlEntry(&pblip->pblipg->dlBlips, pblip);
    AppendDlEntry(&B_002DEB00, pblip);
}
