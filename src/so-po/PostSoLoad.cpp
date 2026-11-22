// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"

extern "C" {
void PostLoLoad(LO *plo);
void UpdateAloXfWorld(SO *pso);
void BindGlobset(void *pglobset);

void PostSoLoad(SO *pso) {
    PostLoLoad(pso);
    UpdateAloXfWorld(pso);
    BindGlobset(&pso->field_0x80);
}
}
