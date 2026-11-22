// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"
#include "xf.h"
#include "stepguard.h"
extern "C" { extern QW g_2a2dd0; void func_0012E460(void *); void *func_0012DC18(void *, void *, int, int, int, QW); }
void func_0020AC28(STEPGUARD *pguard, XF *paim, int pxfLookFrom, QW vecLook)
{
    if (pguard->paim != 0) {
        func_0012E460(&pguard->pact);
        pguard->pact = 0;
        pguard->paim = 0;
    }
    pguard->paim = paim;
    if (paim != 0 && paim->pxfParent != 0) {
        void *pact = func_0012DC18(pguard, paim->pxfParent, 5, 8, 3, g_2a2dd0);
        pguard->pact = pact;
        pguard->field_0xF10 = pxfLookFrom;
        pguard->vecLook = vecLook;
    }
}
