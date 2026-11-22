/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* a SLOTSO override of SO slot 26: pso and pool pass straight through to func_001CB518 (slotso.h is C++ only, so pso stays opaque) */
void func_001CB518(void *pso, void *pool);
void func_001B0D90(void *pso);

void func_001B0D60(void *pso, void *pool) {
    func_001CB518(pso, pool);
    func_001B0D90(pso);
}
