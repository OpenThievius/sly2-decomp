// SPDX-License-Identifier: GPL-3.0-or-later
#include "cplcy.h"
#include "sly2.h"
extern "C" {
extern float g_2dded0;
extern float g_3e1be0;
void ActivateCplcy(K30CAM *, void *, void *);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, int);
void VirtualRefPtr_Assign(void **, void *);
void PauseAmb(void *);
void SetCmNearClip(CM *, float);
void bevy_classes_k30_cam_150ef0(K30CAM *);
void DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(MATRIX3 *pmat, float *ppan, float *ptilt);

// Retail keeps &B_002DDF40 in $s0 from the DecomposeRotateMatrixPanTilt call on (matrix at +0x60, fov at
// +0x24, counter at +0x4A4) and computes &pan (a1) before &tilt (a2). A local camera pointer taken at the
// call with the matrix as a typed member, and the arguments in pan, tilt order, give that base register and
// that order; casting a char array member or writing the global directly moves the address arithmetic.
// ActivateCplcy gets the incoming arguments unchanged (retail never touches a1/a2 before the call).
void bevy_classes_k30_cam_activate_2(K30CAM *pcpz, void *pso, void *pv)
{
    ActivateCplcy(pcpz, pso, pv);
    void *pamb = NewEmitter(0x26);
    SetEmitterUnpositioned(pamb, 0);
    VirtualRefPtr_Assign(&pcpz->field_0xC0, pamb);
    pamb = NewEmitter(0x25);
    SetEmitterUnpositioned(pamb, 0);
    VirtualRefPtr_Assign(&pcpz->field_0xC4, pamb);
    PauseAmb(pcpz->field_0xC0);
    CM *camera = &B_002DDF40;
    DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1((MATRIX3 *)&camera->mat, &pcpz->radPan, &pcpz->radTilt);
    pcpz->radTilt = 0;
    pcpz->distance = 0;
    pcpz->rate = 0;
    pcpz->fovMin = camera->radFovTarget / pcpz->field_0xB4;
    pcpz->fovMax = camera->radFovTarget;
    SetCmNearClip(camera, 49.0f);
    bevy_classes_k30_cam_150ef0(pcpz);
    camera->cplook.cActivate += 1;
    g_3e1be0 = g_2dded0;
}
}
