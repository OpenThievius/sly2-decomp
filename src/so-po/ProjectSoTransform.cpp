#include "sly2.h"
#include "xf.h"
#include "geom.h"
#include "phys.h"
#include "so.h"
extern "C" {
extern float g_2dded0[];
void func_001F3900(SO *);
void IntegrateCloth(GEOM *, float);
void func_001F38A8(GEOM *);
int FXfKindDynamic(int);
void bevy_physics_driven_22de88(SO *);
void ProjectSoTransform(SO *pso)
{
    int index;
    func_001F3900(pso);
    for (index = 0; index < pso->cgeom; index++) {
        GEOM *pgeom = &pso->ageom[index];
        if ((u32)pgeom->grf != 0) IntegrateCloth(pgeom, g_2dded0[1]);
    }
    PHYS *pphys = pso->pphys;
    if (pphys != 0) {
        if (pso->pxfLinear != 0) pphys->linear = pso->pxfLinear->vel;
        if (pso->pxfAngular != 0) pso->pphys->angular = pso->pxfAngular->vel;
        if ((unsigned short)(pso->pxfLinear->kind - 1) < 2 || pso->pxfAngular->kind == 1 || pso->pxfAngular->kind == 2) {
            if (FXfKindDynamic(pso->pxfLinear->kind)) {
                XF *pxf = pso->pxfLinear;
                int *accel = pxf->accel;
                accel[2] = 0;
                accel[1] = 0;
                pxf->accel[0] = 0;
            }
            if (FXfKindDynamic(pso->pxfAngular->kind)) {
                XF *pxf = pso->pxfAngular;
                int *accel = pxf->accel;
                accel[2] = 0;
                accel[1] = 0;
                pxf->accel[0] = 0;
            }
            pso->Slot70();
        }
    }
    bevy_physics_driven_22de88(pso);
    for (index = 0; index < pso->cgeom; index++) {
        GEOM *pgeom = &pso->ageom[index];
        if ((pgeom->grf & 0x4000000000000UL) == 0) func_001F38A8(pgeom);
    }
}
}
