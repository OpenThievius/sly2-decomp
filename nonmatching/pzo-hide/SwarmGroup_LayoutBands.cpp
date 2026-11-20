#include "sly2.h"
struct B8 { char b[8]; };
struct RIDER { char pad[0x2C]; B8 band; B8 outer; char pad2[0x60 - 0x3C]; RIDER *pnext; };
struct GROUP { char pad[8]; int bandMax; int alive; RIDER *pfirst; char pad2[0x20 - 0x14]; float gap; int crv; };
extern "C" float SMaxCrv(int);
struct LAY { float bandMin, bandMax; char pad[8]; float outerMin, outerMax; };
extern "C" void SwarmGroup_LayoutBands(void *pswarm, GROUP *pgroup)
{
    float sCurve = SMaxCrv(pgroup->crv);
    int alive = pgroup->alive;
    float gap = pgroup->gap;
    int riders = pgroup->bandMax;
    if (alive <= riders) riders = alive;
    float aliveF = (float)alive;
    float ridersF = (float)riders;
    float countF = (float)((alive - riders) + 1);
    float lastF = (float)(riders - 1);
    float gapMax = (sCurve * 0.5f) / aliveF;
    gap = gapMax < gap ? gapMax : gap;
    float bandEnd = ((ridersF + ridersF) - 1.0f) * gap;
    float perBand = (sCurve - (aliveF + aliveF) * gap) / countF;
    float gap2 = gap + gap;
    float step = perBand + gap2;
    float shift = step * lastF;
    float bandMax = (bandEnd + ridersF * perBand) - shift;
    float bandMin = bandEnd - shift;
    float outerMin = bandMin - ridersF * gap;
    float outerMax = bandMax + ridersF * gap;
    LAY lay;
    lay.bandMin = bandMin; lay.bandMax = bandMax; lay.outerMin = outerMin; lay.outerMax = outerMax;
    for (RIDER *prider = pgroup->pfirst; prider; prider = prider->pnext) {
        prider->band = *(B8 *)&lay.bandMin;
        prider->outer = *(B8 *)&lay.outerMin;
        lay.bandMin += step; lay.bandMax += step; lay.outerMin += step; lay.outerMax += step;
    }
}
