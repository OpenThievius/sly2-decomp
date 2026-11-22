// SPDX-License-Identifier: GPL-3.0-or-later
#include "act.h"
#include "alo.h"
#include "xf.h"

extern "C" void func_0022C818(ALO *, XF *);
void SetXfKind(ALO *, XF *, int);

extern "C" void RefreshXfActSegment(ALO *palo, XF *pxf) {
    float value = *pxf->ptMin;
    if (value < pxf->tMin || pxf->tMax < value || pxf->sub >= 3) {
        ACT *pact = pxf->pactFirst;
        if (pact != 0) {
            ACTVT *vt = (ACTVT *)pact->vtable;
            vt->slot4.fn((char *)pact + vt->slot4.delta);
            switch (pxf->kind) {
            case 10:
                if ((unsigned short)pxf->sub - 3U >= 2U) {
                    if (pxf->sub != 2)
                        SetXfKind(palo, pxf, 6);
                    break;
                }
                SetXfKind(palo, pxf, 7);
                break;
            case 6:
                if ((unsigned short)pxf->sub - 3U < 2U)
                    SetXfKind(palo, pxf, 7);
                break;
            case 0x13:
                if (pxf->sub != 2)
                    SetXfKind(palo, pxf, 0x12);
                break;
            case 12:
                if (pxf->sub != 2)
                    SetXfKind(palo, pxf, 0xB);
                break;
            }
        } else {
            pxf->sub = 0;
            func_0022C818(palo, pxf);
            SetXfKind(palo, pxf, 0);
        }
    }
}
