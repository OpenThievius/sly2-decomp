// SPDX-License-Identifier: GPL-3.0-or-later
#include "gadgetobj.h"

extern "C" {
int FIgnoreSoIntersection(SO *pso, SO *psoOther);
int FIsBasicDerivedFrom(void *pbasic, int cid);
int IMax(int, int);

int FIgnoreGadgetObjIntersection(GADGETOBJ *pgadget, SO *psoOther) {
    int fIgnore = FIgnoreSoIntersection(pgadget, psoOther);
    int state = pgadget->state;
    if ((state == 0) || (state == 4)) {
        if (FIsBasicDerivedFrom(psoOther, 0x34) != 0) {
            fIgnore = IMax(fIgnore, 1);
        }
    }
    return fIgnore;
}
}
