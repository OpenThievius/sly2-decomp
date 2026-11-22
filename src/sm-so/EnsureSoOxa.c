/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "soview.h"

void RecalcSwOxfFilterForObject(void *, struct SOVIEW *);
struct SOVIEW *func_001F2798(struct SOVIEW *);
extern char B_003DD490;

void EnsureSoOxa(struct SOVIEW *pso) {
    struct SOVIEW *psoRoot;
    const struct SOVT *vt;

    if (pso->poxa == 0) {
        psoRoot = func_001F2798(pso);
        if (psoRoot->poxa == 0) {
            vt = psoRoot->vt;
            psoRoot->poxa = vt->pfnPoxaAlloc((char *)psoRoot + vt->deltaPoxaAlloc);
            RecalcSwOxfFilterForObject(&B_003DD490, psoRoot);
        }
        pso->poxa = psoRoot->poxa;
    }
}
