#include "cplcy.h"
extern "C" {
void StopAmb(void *, float);
void VirtualRefPtr_Assign(void *, void *);
int FIsBasicDerivedFrom(void *, int);
void bevy_camera_cm_14d8d8(void *, float, float);
void DeactivateCplcy(void *, void *, void *);
}

void DeactivateCplook(CPLOOK *look, void *soFocus, void *pv)
{
    void **zoom = &look->ambience;
    if (zoom) {
        if (*zoom) {
            StopAmb(*zoom, 0.0f);
            VirtualRefPtr_Assign(zoom, 0);
        }
    }
    void **binoc = &look->field_0x38;
    if (binoc) {
        if (*binoc) {
            StopAmb(*binoc, 0.5f);
            VirtualRefPtr_Assign(binoc, 0);
        }
    }
    if (FIsBasicDerivedFrom((void *)look->active, 0x34))
        bevy_camera_cm_14d8d8(&B_002DDF40, look->radPan + 3.14159274f, -look->radTilt);
    else
        bevy_camera_cm_14d8d8(&B_002DDF40, look->radPanSaved + 3.14159274f, -look->radTiltSaved);
    DeactivateCplcy(look, soFocus, pv);
}
