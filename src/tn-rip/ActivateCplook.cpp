#include "sly2.h"
#include "cplcy.h"
#include "clock.h"
struct B8 { char b[8]; };
extern "C" {
extern const B8 D_002BD950, D_002BD958, D_002BD968, D_002BD970;
extern char D_002BD960[];
extern float B_FLT_003E1BE0;
void ActivateCplcy(CPLOOK *);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, void *);
void VirtualRefPtr_Assign(void *, void *);
void PauseAmb(void *);
void DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(void *, float *, float *);
int FIsBasicDerivedFrom(void *, int);
void *PmatLoWorld(void *);
float GLimitLm__FP2LMf(void *, float);
void SetCmNearClip(void *, float);
}
extern "C" void ActivateCplook(CPLOOK *pcplook)
{
    ActivateCplcy(pcplook);
    void *emitterZoom = NewEmitter(0x26);
    SetEmitterUnpositioned(emitterZoom, 0);
    VirtualRefPtr_Assign(&pcplook->ambience, emitterZoom);
    void *emitterBinoc = NewEmitter(0x25);
    SetEmitterUnpositioned(emitterBinoc, 0);
    VirtualRefPtr_Assign(&pcplook->field_0x38, emitterBinoc);
    PauseAmb(pcplook->ambience);
    CM *pcmView = &B_002DDF40;
    DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(&pcmView->mat, &pcplook->radPan, &pcplook->radTilt);
    if (FIsBasicDerivedFrom((void *)pcplook->active, 0x34)) {
        *(B8 *)&pcplook->radPanMin = D_002BD950;
        *(B8 *)&pcplook->radTiltMin = D_002BD958;
    } else {
        *(B8 *)&pcplook->radPanMin = D_002BD968;
        *(B8 *)&pcplook->radTiltMin = D_002BD970;
        pcplook->radPanSaved = pcplook->radPan;
        pcplook->radTiltSaved = pcplook->radTilt;
        void *viewer = PmatLoWorld((void *)pcplook->active);
        DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1(viewer, &pcplook->radPan, &pcplook->radTilt);
        float radTilt = GLimitLm__FP2LMf(D_002BD960, pcplook->radTilt);
        pcplook->radTilt = radTilt;
        pcplook->radPanMin += pcplook->radPan;
        pcplook->radPanMax += pcplook->radPan;
        pcplook->radTiltMin += radTilt;
        pcplook->radTiltMax += radTilt;
        pcplook->radTiltMin = GLimitLm__FP2LMf(D_002BD960, radTilt);
        pcplook->radTiltMax = GLimitLm__FP2LMf(D_002BD960, pcplook->radTilt);
    }
    CM *pcm = &B_002DDF40;
    pcplook->dradPan = 0;
    pcplook->dradTilt = 0;
    pcplook->u = 0;
    pcplook->du = 0;
    pcplook->fovMin = pcm->radFovTarget / pcplook->field_0x28;
    pcplook->fovMax = pcm->radFovTarget;
    SetCmNearClip(pcm, 49.0f);
    pcplook->cActivate = pcplook->cActivate + 1;
    B_FLT_003E1BE0 = g_2dded0.t;
}
