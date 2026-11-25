#include "sly2.h"
#include "rip.h"
struct Rows { QW row[3]; };
extern "C" {
int FRenderRipPosMat__FP3RIPP2CMP6VECTORP7MATRIX3(RIP *, QW, Rows *);
void RemoveRip(RIP *);
}
extern "C" void RenderRip(RIP *prip)
{
    QW pos = prip->pos;
    Rows mat;
    mat.row[0] = prip->field_0x40;
    mat.row[1] = prip->field_0x50;
    mat.row[2] = prip->field_0x60;
    if (FRenderRipPosMat__FP3RIPP2CMP6VECTORP7MATRIX3(prip, pos, &mat) == 0)
        RemoveRip(prip);
}
