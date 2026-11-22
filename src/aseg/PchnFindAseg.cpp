// SPDX-License-Identifier: GPL-3.0-or-later
#include "alo.h"
#include "asega.h"
#include "xf.h"

ASEGCHN *PchnFindAseg(ASEG *paseg, SO *pso, int dof, int fStripOnly)
{
    int ichn = 0;
    while (ichn < paseg->cchn) {
        ASEGCHN *pchn = &paseg->achn[ichn];
        if (fStripOnly == 0 || (pchn->grf & 0x40000000) != 0) {
            unsigned grf = pchn->grf;
            if (((int)(grf << 12) >> 12) == pso->oid && (grf & 0x80000000) == 0) {
                XF *pxf = (XF *)pso->PxfFromRef((int)(grf << 2) >> 22);
                if (pxf->dof == dof)
                    return pchn;
            }
        }
        ichn++;
    }
    return 0;
}
