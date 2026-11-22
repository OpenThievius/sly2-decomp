// SPDX-License-Identifier: GPL-3.0-or-later
#include "lookat.h"
#include "xf.h"

extern "C" {
void func_0022C818(ALO *palo, XF *pxf);
extern QW g_2a2dd0;

void func_0012D088(LOOKATGOAL *plookat) {
    XF *pxf;

    pxf = plookat->pxf;
    pxf->posGoal = plookat->posTarget;
    plookat->pxf->velGoal = g_2a2dd0;
    plookat->pxf->sub = plookat->xfSub;
    func_0022C818(plookat->palo, plookat->pxf);
}

}
