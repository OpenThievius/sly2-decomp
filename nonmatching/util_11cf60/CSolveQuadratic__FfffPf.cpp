#include "sly2.h"
int CSolveQuadratic(float a, float b, float c, float *roots)
{
    float bCopy = b;
    float cTimesFour = c * 4.0f;
    float bSquared = bCopy * bCopy;
    float discriminant = bSquared - a * cTimesFour;
    if (discriminant < 0.0f)
        return 0;
    float twoA = a + a;
    float spread = __builtin_sqrtf(discriminant) / twoA;
    if (__builtin_fabsf(spread) < 0.0001f) {
        roots[0] = -(bCopy / twoA);
        return 1;
    }
    float center = -(bCopy / twoA);
    float high = center + spread;
    float low = center - spread;
    roots[1] = low;
    roots[0] = high;
    if (low < high) {
        roots[0] = low;
        roots[1] = high;
    }
    return 2;
}
