// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
#include "phys.h"
#include "xf.h"

extern "C" {
void SetXfKind(SO *, XF *, int);
void ConstrFromCnstr(SO *, XF *, int, void *);
void RecalcSoLocked(SO *);
void func_001F8668(SO *, int);

void SetSoCnstrTorque(SO *pso, int cnstr) {
    if (pso->pphys) {
        XF *pxf = pso->pxfAngular;
        if (pxf->pactFirst == 0) {
            if (pxf->kind != 2)
                SetXfKind(pso, pxf, 1);
        }
        ConstrFromCnstr(pso, pxf, cnstr, &pso->pphys->cnstrTorque);
        RecalcSoLocked(pso);
        if (pso->pphys->ctTorque != 3)
            func_001F8668(pso, 0);
    }
}
}
