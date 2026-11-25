#include "blip.h"
struct SHD { u8 unknown_0x0[8]; unsigned flags; unsigned char color[4]; int cframe; s64 *apacket; };
struct PK { s64 packet; int six; int keep; };
extern "C" SHD *PshdframesOrFirst(int);
extern "C" char B_002DD600;
extern "C" char B_002DD5C0;
extern "C" void PropagateBlipgShader__FP5BLIPG(BLIPG *pblipg, int oidShader)
{
    SHD *pshd = PshdframesOrFirst(oidShader);
    pblipg->pgifs = (pshd->flags & 1) ? &B_002DD600 : &B_002DD5C0;
    if (pblipg->hasColor == 0) {
        pblipg->hasColor = 1;
        for (int ib = 0; ib < 4; ib++)
            pblipg->color[ib] = (pshd->color[ib] + 1) >> 1;
    }
    int cduplicate = 0;
    int cqw = 1;
    for (int shifted = pshd->cframe >> 1; shifted != 0; shifted >>= 1)
        cqw <<= 1;
    int cframe = pshd->cframe;
    cqw <<= (cqw < cframe) ? 1 : 0;
    while (cqw > 31)
        cqw >>= 1;
    if (cframe < cqw) {
        int diff = cqw - cframe;
        cduplicate = diff;
    }
    pblipg->cqwTexture = cqw;
    QW *pqw = pblipg->aqw;
    for (int iframe = 0; iframe < cframe; iframe++) {
        s64 packet = pshd->apacket[iframe];
        ((PK *)pqw)->six = 6;
        ((PK *)pqw)->packet = packet;
        if (iframe < cduplicate) {
            pqw[1] = pqw[0];
            pqw++;
        }
        pqw++;
    }
}
