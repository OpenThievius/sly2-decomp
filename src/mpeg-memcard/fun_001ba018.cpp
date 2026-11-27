// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "vu0inline.h"
#include "xf.h"
#include "stepguard.h"
extern "C" void PostGuardLoad(ZONEGUARD *);
extern "C" void SetSoProperties(ZONEGUARD *, int, const void *);
extern "C" float *PeaFindAsegLabel(void *, int);
extern "C" void PredictAsegEffect(float, float, void *, ZONEGUARD *, void *, int, QW *, int);
extern "C" float SetSoMass__FP2SOf(ZONEGUARD *, float);
extern char D_002C0A50[];

void func_001BA018(ZONEGUARD *g)
{
    QW mat[4];
    PostGuardLoad(g);
    SetSoProperties(g, 3, D_002C0A50);
    float *t = PeaFindAsegLabel(g->pasegLook, 0x5DB);
    PredictAsegEffect(*t, 1.0f, g->pasegLook, g, g->pxfPredict, (int)(g->pxfLook)->pxfParent, mat, 0);
    XF *xf = g->pxfLook;
    g->vecLook = VectorSub(mat[3], xf->mat.row[3]);
    g->animrefLook.kind = 0;
    g->animrefLook.grf = 1;
    SetSoMass__FP2SOf(g, 0.25f);
}
