#include "sly2.h"
// Sqrt: sqrt.s with an early-clobber output (=&f); retail's helper keeps the result out of the operand's register.
static inline float Sqrt(float x) { float r; asm volatile("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
struct CRV { char pad0[0xE4]; int closed; };
extern "C" {
float SMaxCrv(CRV *);
float SWrapCrv(float, CRV *);
float GRandInRange(float, float);
extern int g_2c3650;
}
float SRandNearCrv(CRV *pcrv, float s, float ds)
{
    float bounds[2];
    float sLow, sHigh;
    if (pcrv->closed != 0) {
        sHigh = s + ds;
        sLow = s - ds;
    } else {
        float sMax = SMaxCrv(pcrv);
        float sCenter;
        if (s < ds) {
            sCenter = ds;
        } else {
            float sLimit = sMax - ds;
            sCenter = s;
            if (sLimit < s)
                sCenter = sLimit;
        }
        float sTop = sCenter + ds;
        sHigh = (sTop < sMax) ? sTop : sMax;
        float sBottom = sCenter - ds;
        sLow = (0.0f < sBottom) ? sBottom : 0.0f;
    }
    bounds[0] = sLow;
    bounds[1] = sHigh;
    float gRand = GRandInRange(-1.0f, 1.0f);
    if (g_2c3650 == 1) {
        gRand = gRand * (gRand < 0.0f ? -gRand : gRand);
    } else if (g_2c3650 == 2) {
        float gSign = (0.0f < gRand) ? 3.0f : -3.0f;
        gRand = gRand * gRand * (gSign - (gRand + gRand));
    } else if (g_2c3650 == 3) {
        if (0.0f < gRand)
            gRand = Sqrt(gRand);
        else
            gRand = -Sqrt(-gRand);
    }
    float unit = gRand * 0.5f + 0.5f;
    float result = (1.0f - unit) * bounds[0] + unit * bounds[1];
    if (pcrv->closed != 0)
        return SWrapCrv(result, pcrv);
    return result;
}
