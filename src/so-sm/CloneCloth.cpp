#include "geom.h"
#include "vu0inline.h"
#include "sly2.h"
#include "alloc.h"
#include "ps2inline.h"
#include "xf.h"

struct BSPC;
struct VECSET { s32 count; QW *avec; u8 unknown_0x8[0x10]; };
/* the 0xB0-byte collision element (geom.h) of a cloth: its vertices are the VECSET at 0x78 (field_0x78), CloneGeom copies them into the one at 0x90 */
struct CLOTH : GEOM {};

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
    dest->pso = source->pso;
    dest->alo = source->alo;
    dest->cfixed = source->cfixed;
    float maxLengthSquared = 0.0f;
    for (int index = 0; index < ((VECSET *)source->field_0x78)->count; index++) {
        float lengthSquared = LaneX(SquaredLength(((VECSET *)source->field_0x78)->avec[index]));
        if (maxLengthSquared < lengthSquared)
            maxLengthSquared = lengthSquared;
    }
    dest->radius = Sqrt(maxLengthSquared);
    local = *(VECSET *)source->field_0x78;
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
    CloneGeom(&local, &matrix, (VECSET *)dest->field_0x78);
    CloneGeom((VECSET *)dest->field_0x78, &pxf->matWorld, (VECSET *)dest->field_0x90);
    CloneBspc((GEOM *)source->field_0x68, (BSPC *)source->field_0x90, (GEOM *)dest->field_0x68, (BSPC *)dest->field_0x90);
    CStackFrame_Destructor(frame, 2);
}
