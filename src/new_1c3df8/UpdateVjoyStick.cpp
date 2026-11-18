/* SPDX-License-Identifier: GPL-3.0-or-later */
struct VJOY;
extern "C" float atan2f(float, float);
extern "C" float RadNormalize__Ff(float);
extern "C" int CalculateSinCos__FfPfT1(float, float *, float *);
static inline float Sqrt(float x) { float r; asm volatile("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
static inline float GMax(float a, float b) { return a < b ? b : a; }
extern "C" void UpdateVjoyStick(float radPan, VJOY *pvjoy, float *px, float *py, float *prad, float *ps, float *psHold)
{
    float gSin, gCos;
    float x = *px;
    float y = *py;
    float sum = x * x + y * y;
    float len = Sqrt(sum);
    *ps = len;
    float hold = GMax(*psHold - 0.2f, 0.0f);
    *psHold = hold;
    if (*ps < hold || *ps == 0.0f) {
        CalculateSinCos__FfPfT1((*prad - radPan) + 1.5707964f, &gSin, &gCos);
        float held = *psHold;
        *ps = held;
        *px = held * gCos;
        *py = *ps * gSin;
    } else {
        *prad = RadNormalize__Ff((atan2f(*py, *px) + radPan) - 1.5707964f);
        *psHold = *ps;
    }
}
