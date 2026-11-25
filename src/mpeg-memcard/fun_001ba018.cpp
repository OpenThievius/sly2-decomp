// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "vu0inline.h"
#include "xf.h"
struct GL { u8 unknown_0x0[0x1020]; void *paseg; u8 unknown_0x1028[0xC]; void *xfa; void *xfb; u8 unknown_0x1038[0x1040-0x1038]; QW off; u8 unknown_0x1050[0x1060-0x1050]; int f1060; u8 unknown_0x1064[0x106C-0x1064]; int f106c; };
extern "C" void PostGuardLoad(GL *);
extern "C" void SetSoProperties(GL *, int, const void *);
extern "C" float *PeaFindAsegLabel(void *, int);
extern "C" void PredictAsegEffect(float, float, void *, GL *, void *, int, QW *, int);
extern "C" float SetSoMass__FP2SOf(GL *, float);
extern char D_002C0A50[];

void func_001BA018(GL *g)
{
    QW mat[4];
    PostGuardLoad(g);
    SetSoProperties(g, 3, D_002C0A50);
    float *t = PeaFindAsegLabel(g->paseg, 0x5DB);
    PredictAsegEffect(*t, 1.0f, g->paseg, g, g->xfa, (int)((XF *)g->xfb)->pxfParent, mat, 0);
    XF *xf = (XF *)g->xfb;
    g->off = VectorSub(mat[3], xf->mat.row[3]);
    g->f1060 = 0;
    g->f106c = 1;
    SetSoMass__FP2SOf(g, 0.25f);
}
