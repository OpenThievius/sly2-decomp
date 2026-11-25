#include "vu0inline.h"
#include "sly2.h"
#include "alloc.h"
#include "ps2inline.h"
#include "xf.h"

struct GEOM;
struct BSPC;
struct VECSET { s32 count; QW *avec; u8 unknown_0x8[0x10]; };
struct CLOTH {
    XF *pxf;
    s32 field_0x4;
    float radius;
    s32 field_0xC;
    u8 unknown_0x10[0xC];
    int cfixed;
    u8 unknown_0x20[0x68 - 0x20];
    char bspc0[0x10];
    VECSET vecset;
    char bspc1[0x18];
};

extern "C" {
void *CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
void *PvAllocStackClearImpl__Fi(ALLOCREQ *);
void CloneGeom(VECSET *, const MATRIX4 *, VECSET *);
}
MATRIX4 InvertMatrix4Affine(const MATRIX4 *);
MATRIX4 operator*(const MATRIX4 &, const MATRIX4 &);
void CopyAb(void *, void *, unsigned int);
void CloneBspc(GEOM *, BSPC *, GEOM *, BSPC *);
static inline float Sqrt(float x) { float r; asm volatile("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }

void CloneCloth(CLOTH *source, XF *pxf, int cadd, CLOTH *dest)
{
    MATRIX4 matrix;
    VECSET local;
    char frame[0x10];
    ALLOCREQ req;
    CStackFrame_Construct(frame);
    dest->pxf = pxf;
    dest->field_0x4 = source->field_0x4;
    dest->field_0xC = source->field_0xC;
    dest->cfixed = source->cfixed;
    float maxLengthSquared = 0.0f;
    for (int index = 0; index < source->vecset.count; index++) {
        float lengthSquared = LaneX(SquaredLength(source->vecset.avec[index]));
        if (maxLengthSquared < lengthSquared)
            maxLengthSquared = lengthSquared;
    }
    dest->radius = Sqrt(maxLengthSquared);
    local = source->vecset;
    ALLOCREQ *preq = &req;
    req.cb = (local.count + cadd) * 0x10;
    preq->cbAlign = 0x10;
    char *newvec = (char *)PvAllocStackClearImpl__Fi(preq);
    int cfixed = source->cfixed;
    int bytesFixed = cfixed * 0x10;
    CopyAb(newvec, local.avec, bytesFixed);
    CopyAb(newvec + (cfixed + cadd) * 0x10, (char *)local.avec + bytesFixed, (local.count - cfixed) * 0x10);
    local.avec = (QW *)newvec;
    local.count += cadd;
    matrix = InvertMatrix4Affine(&pxf->matWorld) * source->pxf->matWorld;
    CloneGeom(&local, &matrix, &dest->vecset);
    CloneGeom(&dest->vecset, &pxf->matWorld, (VECSET *)dest->bspc1);
    CloneBspc((GEOM *)source->bspc0, (BSPC *)source->bspc1, (GEOM *)dest->bspc0, (BSPC *)dest->bspc1);
    CStackFrame_Destructor(frame, 2);
}
