// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"

extern "C" {
void func_001A58D0(LO *plo, LO *ploParent, int grf);
QW PosLoWorld(LO *plo);
void ExplodeGadgetBurst(GADGETOBJ *pgadget, int word1, int word2, QW origin, float radius);

void DetonateGadgetObj(GADGETOBJ *pgadget, float radius) {
    QW position;

    func_001A58D0(pgadget, 0, 1);
    position = PosLoWorld(pgadget);
    ExplodeGadgetBurst(pgadget, pgadget->field_0x174, pgadget->field_0x178, position, radius);
}
}
