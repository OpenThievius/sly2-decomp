// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"

struct LIST;

extern "C" {
CRef func_002013D8(LIST *plist, int otyp, int unused, int *pcState, int *astate);
int GrfOfStates(int cstate, int *astate);

int func_00162050(LIST *plist) {
    int astate[8];
    int cstate;
    CRef ref = func_002013D8(plist, 0x1050, 6, &cstate, astate);
    return GrfOfStates(cstate, astate);
}

}
