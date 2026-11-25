#include "guard.h"
#include "cm.h"
extern "C" float atan2f(float, float);
float GetAlertPan(ALERT *palert)
{
    float rad = 0.0f;
    int mode = palert->field_0x10;
    switch (mode) {
 case 0: rad = atan2f(B_002DDF40.mat.mat[0][1], B_002DDF40.mat.mat[0][0]); break;
 case 1: {
        MATRIX4 *first = palert->palo->PmatWorld();
        MATRIX4 *second = palert->palo->PmatWorld();
        rad = atan2f(first->mat[0][1], second->mat[0][0]);
} break; case -1: break; default: break; }
    return rad;
}
