#include "sly2.h"
#include "xf.h"
#include "so.h"
#include "cm.h"
extern float g_2dded0[];
extern "C" QW VelocityXfAtPos(XF *, void *, QW);
void TiltMatUpright(MATRIX3 *, MATRIX3 *, MATRIX3 *);
extern "C" float atan2f(float, float);

void GetSoCpdefi(SO *so, float dt, CPDEFI *cp)
{
    XF *xf = so->pxfRoot;
    MATRIX3 *mat = (MATRIX3 *)&xf->matWorld;
    QW pos = xf->matWorld.row[3];
    cp->pos = pos;
    cp->vel = VelocityXfAtPos(xf, 0, pos);
    MATRIX3 up;
    TiltMatUpright(mat, 0, &up);
    cp->radHome = atan2f(-up.mat[0][1], -up.mat[0][0]);
    cp->sAdjust = 100.0f;
    cp->grfcpd = 0;
    cp->tMoveLast = g_2dded0[0];
    cp->cfk = 0;
}
