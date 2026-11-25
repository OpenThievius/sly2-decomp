#include "cplcy.h"

extern "C" int FFloatsNear__Ffff(float, float, float);

int func_001510D8(K30CAM *self) {
    float value = self->minDistance;
    int result = 0;
    if (value < 0.0f || FFloatsNear__Ffff(self->distance, value, 0.01f)) {
        result = 1;
    }
    return result;
}
