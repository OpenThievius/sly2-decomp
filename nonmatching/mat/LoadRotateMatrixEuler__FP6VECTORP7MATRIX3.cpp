// SPDX-License-Identifier: GPL-3.0-or-later
#include "ps2inline.h"
#include "sly2.h"
void CalculateSinCos__FfPfT1(float rad, float *pgSin, float *pgCos);
extern "C" MATRIX3 *LoadRotateMatrixEuler__FP6VECTORP7MATRIX3(MATRIX3 *pmatResult, QW eul)
{
    float gSinX, gCosX, gSinY, gCosY, gCosZ, gSinZ;
    CalculateSinCos__FfPfT1(LaneX(eul), &gSinX, &gCosX);
    float y = LaneYInGeneralRegister(eul);
    CalculateSinCos__FfPfT1(y, &gSinY, &gCosY);
    float z = LaneZInGeneralRegister(eul);
    CalculateSinCos__FfPfT1(z, &gSinZ, &gCosZ);
    float *ag = (float *)pmatResult;
    ag[5] = gSinX * gSinY * gSinZ + gCosX * gCosZ;
    ag[1] = gCosY * gSinZ;
    ag[4] = gSinX * gSinY * gCosZ - gCosX * gSinZ;
    ag[0] = gCosY * gCosZ;
    ag[9] = gCosX * gSinY * gSinZ - gSinX * gCosZ;
    ag[6] = gSinX * gCosY;
    ag[8] = gCosX * gSinY * gCosZ + gSinX * gSinZ;
    ag[2] = -gSinY;
    ag[10] = gCosX * gCosY;
    return pmatResult;
}
