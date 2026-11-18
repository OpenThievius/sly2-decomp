#include "types.h"
struct KEY { float a, b, c, sDuration, t; };
struct SEG { char pad0[4]; int nState; char pad1[0x14 - 8]; float s; int ckey; KEY akey[6]; int ikey; char pad2[0xA0 - 0x98]; };
struct BEAM { SEG aseg[2]; float sFull; float sClipped; int cHit; char pad[0x150 - 0x14C]; };
struct DLOWNER { char pad[0x70]; u64 grf; };
struct LASER { char pad0[0xEC]; DLOWNER *powner; char pad1[0x198 - 0xF0]; int cbeam; BEAM *abeam; char pad2[0x1C0 - 0x1A0]; float dt; };
extern "C" {
void GetLaserBeamPoints(LASER *, BEAM *, QW *, float *);
void AppendDlEntry(void *, void *);
float fmodf(float, float);
extern char B_003E11C4[];
extern float g_2dded0[];
}

void AdvanceLaserBeams(LASER *plaser)
{
    for (int ibeam = 0; ibeam < plaser->cbeam; ibeam++) {
        BEAM *pbeam = &plaser->abeam[ibeam];
        int fActive = 0;
        SEG *pseg = pbeam->aseg;
        do {
            if (pseg->nState == 1) {
            KEY *pkey = &pseg->akey[pseg->ikey];
            pkey->t = pkey->t + plaser->dt * g_2dded0[1];
            if (pkey->sDuration < pkey->t) {
                float t = fmodf(pkey->t, pkey->sDuration);
                pseg->ikey = (pseg->ikey + 1) % pseg->ckey;
                pkey = &pseg->akey[pseg->ikey];
                pkey->t = t;
            }
            pseg->s = pkey->a + pkey->b * pkey->t + pkey->c * pkey->t * pkey->t * 0.5f;
            if ((plaser->powner->grf & 2) == 0) {
                plaser->powner->grf |= 2;
                AppendDlEntry(B_003E11C4, plaser->powner);
            }
            fActive = 1;
            }
        } while (++pseg < pbeam->aseg + 2);
        if (fActive && pbeam->cHit == 0) {
            QW apos[2];
            float sLength;
            GetLaserBeamPoints(plaser, pbeam, apos, &sLength);
            float sFull = sLength;
            pbeam->sClipped = sFull;
            pbeam->sFull = sFull;
        }
    }
}
