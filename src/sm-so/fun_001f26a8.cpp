// SPDX-License-Identifier: GPL-3.0-or-later
#include "so.h"
extern "C" {
int FIsBasicDerivedFrom(void *, int);
void func_001F2500(SO *);
void func_001F26A8(SO *pso) {
    func_001F2500(pso);
    for (LO *plo = (LO *)pso->dlChild.head; plo != pso->ploChildEnd; plo = plo->ploNext) {
        if (FIsBasicDerivedFrom(plo, 0x30) != 0) {
            func_001F26A8((SO *)plo);
        }
    }
}
}
