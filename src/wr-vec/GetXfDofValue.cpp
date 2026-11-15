// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
union VU_SCALE { QW q; VECTOR v; };
struct XF { char pad[0x94]; unsigned mode; };
extern "C" QW DecomposeRotateMatrixEuler(float *);
// Lanes 0..2 of the vector: pextlw packs x and y, pcpyld adds z
static inline QW Build(float x, float y, float z) {
    return VectorFromFloats3(x, y, z);
}
QW GetXfDofValue(XF *xf, float *mat, QW result) {
    VU_SCALE frame;
    float y, x, z;
    QW built;
    switch (xf->mode) {
    case 1: case 4: case 5: case 9: case 10:
        x = mat[12]; y = mat[13]; z = mat[14];
        goto build;
    case 0: case 15:
        break;
    case 6: case 7:
        result = DecomposeRotateMatrixEuler(mat);
        break;
    case 11:
        x = mat[4]; y = mat[8]; z = mat[9];
    build:
        frame.q = Build(x, y, z);
        result = frame.q;
        break;
    case 12:
        y = mat[5]; x = mat[0]; z = mat[10];
        frame.q = Build(x, y, z);
        result = frame.q;
        break;
    }
    return result;
}
