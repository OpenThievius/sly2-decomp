// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
extern "C" {
void InsertXfAct(ALO *palo, XF *pxf, ACT *pact);                 /* extern */
ACT *PactNewForXf(s32 kind, ALO *palo, XF *pxf, s32 priority, s32 xfk); /* extern */

ACT *CreateXfActadj(ALO *palo, XF *pxf, s32 priority) {
    ACT *pact;

    pact = PactNewForXf(5, palo, pxf, priority, -1);
    InsertXfAct(palo, pxf, pact);
    return pact;
}

}
