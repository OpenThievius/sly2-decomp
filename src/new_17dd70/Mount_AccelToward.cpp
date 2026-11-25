#include "mount.h"
struct M3 { QW row[3]; };
extern "C" QW g_2a2dc0;
extern "C" QW g_2a2dd0;
extern "C" char D_002BE800[];
extern "C" char D_002BE810[];
extern "C" void LoadRotateMatrixRad(M3 *, float, QW);
extern "C" void AccelSoTowardMatSmooth__FP2SOfP7MATRIX3P3SMP(MOUNT *, M3 *, void *);
extern "C" void AccelSoTowardPosSpring(MOUNT *, QW, int, QW, void *);
void Mount_AccelToward(MOUNT *mount)
{
    if (mount->state != 3) {
        M3 copy;
        M3 mat;
        LoadRotateMatrixRad(&mat, mount->radStick, g_2a2dc0);
        copy = mat;
        AccelSoTowardMatSmooth__FP2SOfP7MATRIX3P3SMP(mount, &copy, D_002BE800);
        AccelSoTowardPosSpring(mount, g_2a2dd0, 0, mount->vecStick, D_002BE810);
    }
}
