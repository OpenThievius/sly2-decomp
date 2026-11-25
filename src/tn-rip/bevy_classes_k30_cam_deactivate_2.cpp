#include "cplcy.h"
extern "C" {
void StopAmb(void *, float);
void VirtualRefPtr_Assign(void **, void *);
void SetResetFlag__FP2CM(void *);
void DeactivateCplcy(void *, void *, void *);
void bevy_classes_k30_cam_deactivate_2(K30CAM *pcpz, void *pso, void *pv)
{
    if (&pcpz->field_0xC0) {
        if (pcpz->field_0xC0) {
            StopAmb(pcpz->field_0xC0, 0.0f);
            VirtualRefPtr_Assign(&pcpz->field_0xC0, 0);
        }
    }
    if (&pcpz->field_0xC4) {
        if (pcpz->field_0xC4) {
            StopAmb(pcpz->field_0xC4, 0.5f);
            VirtualRefPtr_Assign(&pcpz->field_0xC4, 0);
        }
    }
    pcpz->field_0x10 = 0;
    pcpz->field_0x14 = 0;
    pcpz->active = 0;
    pcpz->minDistance = -1.0f;
    SetResetFlag__FP2CM(&B_002DDF40);
    DeactivateCplcy(pcpz, pso, pv);
}
}
