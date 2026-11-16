#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
union VU_SCALE { QW q; VECTOR v; };
struct MRSG_138970 { float t; float w; };
struct ACPBLOBJ {
    virtual void Unused();
    virtual void Evaluate(VECTOR *pvectorFirst, VECTOR *pvectorSecond, ACPBLOBJ *pobj, float gFirst, float gSecond);
};
struct ACPBLDEF { char pad0[0x74]; float gPeriod; char pad78[0x48]; int cstride; int ccount; char *abase; };
struct ACPBLTRACK { int offset; int cmrsg; MRSG_138970 *amrsg; };
struct ACPBL { char pad0[4]; ACPBLDEF *pdef; ACPBLTRACK *ptrack; ACPBLOBJ **apobj; VECTOR vectorDefault; };
struct ACPBLCHILD { float gScale; ACPBLDEF *pdef; };
extern VECTOR g_2a2dd0;
extern "C" int ImrsgLookUp__FffiP4MRSGPf(float, float, int, MRSG_138970 *, float *);
void EvaluateAcpbl(ACPBL *pacpbl, VECTOR *pvectorFirst, VECTOR *pvectorSecond, float gTime, float gRate)
{
    VECTOR vectorFirst, vectorSecond, vectorA, vectorB;
    float gDelta;
    float gNorm;
    int imrsg;
    MRSG_138970 *pmrsg;
    if (pacpbl->ptrack == 0) {
        gNorm = gTime / pacpbl->pdef->gPeriod;
    } else {
        imrsg = ImrsgLookUp__FffiP4MRSGPf(gTime, pacpbl->pdef->gPeriod, pacpbl->ptrack->cmrsg, pacpbl->ptrack->amrsg, &gDelta);
        pmrsg = &pacpbl->ptrack->amrsg[imrsg];
        gNorm = gDelta / pmrsg->w;
    }
    vectorFirst = g_2a2dd0;
    vectorSecond = g_2a2dd0;
    for (int i = 0; i < pacpbl->pdef->ccount; i++) {
        ACPBLCHILD *pchild = (ACPBLCHILD *)(pacpbl->pdef->abase + i * pacpbl->pdef->cstride);
        if (pchild->gScale != 0.0f) {
            ACPBLOBJ *pobj = pacpbl->apobj[i];
            if (pobj == 0) {
                vectorSecond.x = 0.0f;
                vectorFirst = pacpbl->vectorDefault;
                vectorSecond.z = 0.0f;
                vectorSecond.y = 0.0f;
            } else {
                float gA, gB;
                if (pacpbl->ptrack == 0) {
                    float gPeriod = pchild->pdef->gPeriod;
                    gB = (gRate * gPeriod) / pacpbl->pdef->gPeriod;
                    gA = gNorm * gPeriod;
                } else {
                    MRSG_138970 *pentry = (MRSG_138970 *)((char *)pchild + pacpbl->ptrack->offset + imrsg * 8);
                    float gLimit = pchild->pdef->gPeriod;
                    gA = pentry->t + gNorm * pentry->w;
                    gB = (gRate * pentry->w) / pmrsg->w;
                    if (gLimit < gA)
                        gA -= gLimit;
                }
                pobj->Evaluate(&vectorA, &vectorB, pobj, gA, gB);
            }
            {
                VU_SCALE scale;
                scale.q = VectorFromWord(*(u32 *)&pchild->gScale);
                *(QW *)&vectorFirst = ScaleAddX(*(QW *)&vectorFirst, *(QW *)&vectorA, scale.q);
            }
            {
                VU_SCALE scale;
                scale.q = VectorFromWord(*(u32 *)&pchild->gScale);
                *(QW *)&vectorSecond = ScaleAddX(*(QW *)&vectorSecond, *(QW *)&vectorB, scale.q);
            }
        }
    }
    if (pvectorFirst != 0)
        *pvectorFirst = vectorFirst;
    if (pvectorSecond != 0)
        *pvectorSecond = vectorSecond;
}
