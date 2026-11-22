// SPDX-License-Identifier: GPL-3.0-or-later
#include "alo.h"
#include "xf.h"

extern "C" void SetXfKind(ALO *, XF *, int);
extern "C" void WakeXf(ALO *palo, XF *pxf)
{
    switch ((short)((unsigned short)pxf->kind - 3)) {
    case 3: case 7:
        SetXfKind(palo, pxf, 7);
        break;
    case 9:
        SetXfKind(palo, pxf, 0xB);
        break;
    case 16:
        SetXfKind(palo, pxf, 0x12);
        break;
    case 0:
        SetXfKind(palo, pxf, 1);
        break;
    }
}
