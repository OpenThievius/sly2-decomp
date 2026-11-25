#include "sly2.h"
#include "cplcy.h"
extern "C" {
extern QW g_2a2dd0;
void ActivateCplcy(void *, int, int);
void SetCmNearClip(void *, float);
void SetCmFov(void *, float);
int func_0012DC18(int, int, int, int, int, QW);
}
extern "C" void bevy_camera_looks_activate(CPCLOSE *close, int focusObj, int xf)
{
    ActivateCplcy(close, focusObj, xf);
    close->xf = xf;
    SetCmNearClip(&B_002DDF40, 25.0f);
    SetCmFov(&B_002DDF40, 1.15f);
    close->lookat = func_0012DC18(close->active, close->xf, 1, 8, 3, g_2a2dd0);
    close->tJiggle = -1.0f;
}
