// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "vu0inline.h"
#include "ps2inline.h"
struct SWX_15B428 { char pad[1]; };
struct LO_15B428;
struct ROWC_15B428 { int i0; int i4; float f8; float fC; } __attribute__((aligned(16)));
struct TABLE_15B428 { VECTOR a; VECTOR b; };
struct BLIP_15B428 {
    VECTOR pos[0x2B]; VECTOR vel[0x2B]; ROWC_15B428 row[0x2B]; char pad0[0x840 - 0x810];
    VECTOR pos2[0x2B]; VECTOR vel2[0x2B]; ROWC_15B428 row2[0x2B]; char pad1[0x1084 - 0x1050];
    unsigned int cblip; TABLE_15B428 *ptable; char pad2[4]; BLIP_15B428 *pblipNext;
};
struct BVTE_15B428 { short delta; short index; void (*fn)(char *, LO_15B428 *); };
struct BLIPGVT_15B428 { char pad[0x198 - 0x10 + 0x10 - 0x10]; };
struct BLIPG_15B428 {
    char pad0[0xC]; char *vt; char pad1[0x160 - 0x10]; int fTable; char pad2[0x1A0 - 0x164]; int cRow;
    char pad3[0x3B0 - 0x1A4]; int cRand; char pad4[0x434 - 0x3B4]; int fEven; char pad5[0x43C - 0x438]; int mode;
    char pad6[0x444 - 0x440]; int cblip; BLIP_15B428 *pblipFirst;
};
struct EMITB_15B428 {
    char pad0[0xC8]; int fRow; char pad1[0xF0 - 0xCC]; int fF0; int fF4; float gMin; float gMax;
};
struct EMITREF_15B428 { LO_15B428 *plo; int pad4; int unk8; };
struct EMITG_15B428 { BLIPG_15B428 **ppblipg; int pad4; int unk8; };
extern SWX_15B428 B_003DD490;
extern char B_002DDF40[];
extern "C" {
BLIPG_15B428 *PblipgNew(SWX_15B428 *);
BLIP_15B428 *PblipNew__FP5BLIPG(SWX_15B428 *, BLIPG_15B428 *);
void SetBlipgEmitb__FP5BLIPGP5EMITB(BLIPG_15B428 *, EMITB_15B428 *);
int NRandInRange(int, int);
float GRandInRange(float, float);
}

void EmitBlips__FP5EMITBP5EMITGiP6VECTORT3PfT5T3T3(EMITB_15B428 *pemitb, EMITG_15B428 *pemitg, int cblip, VECTOR *apos, VECTOR *av, float *atc, float *atd, VECTOR *apos2, VECTOR *av2)
{
    BLIPG_15B428 *pblipg = 0;
    if (pemitg != 0 && pemitg->ppblipg != 0)
        pblipg = *pemitg->ppblipg;
    BLIP_15B428 *pblip;
    if (pblipg != 0) {
        pblip = pblipg->pblipFirst;
    } else {
        pblipg = PblipgNew(&B_003DD490);
        if (pblipg == 0)
            return;
        if (pemitg != 0 && pemitg->ppblipg != 0)
            *pemitg->ppblipg = pblipg;
        SetBlipgEmitb__FP5BLIPGP5EMITB(pblipg, pemitb);
        if (pemitg != 0 && pemitg->unk8 != 0) {
            char *vt = pblipg->vt;
            (*(void (**)(char *, int))(vt + 0x19C))((char *)pblipg + *(short *)(vt + 0x198), pemitg->unk8);
        }
        if (pblipg == 0)
            return;
        pblip = pblipg->pblipFirst;
    }
    for (int iblip = 0;;) {
        if (iblip >= cblip)
            break;
        if (pblip == 0) {
            pblip = PblipNew__FP5BLIPG(&B_003DD490, pblipg);
            if (pblip == 0)
                return;
        }
        unsigned int index = pblip->cblip;
        if (index < 0x2B) {
            while (iblip < cblip) {
                pblip->pos[index] = apos[iblip];
                pblip->pos[index].w = atc[iblip];
                pblip->vel[index] = av[iblip];
                pblip->vel[index].w = atd[iblip];
                ROWC_15B428 *prow = &pblip->row[index];
                memset(prow, 0, 0x10);
                prow->i0 = NRandInRange(0, pblipg->cRand - 1);
                if (pblipg->fEven != 0)
                    prow->i0 &= ~1;
                if (pemitb->fRow != 0)
                    prow->i4 = NRandInRange(0, pblipg->cRow - 1);
                if (pblipg->mode == 2) {
                    float angle = GRandInRange(pemitb->gMin, pemitb->gMax);
                    prow->f8 = angle;
                    if (pemitb->fF0 == 0) {
                        if (LaneX(DotProduct(*(QW *)(B_002DDF40 + 0x70), *(QW *)&pblip->vel[index])) > 0.0f)
                            prow->f8 = -angle;
                    }
                    if (pemitb->fF4 != 0)
                        prow->fC = GRandInRange(-3.1415927f, 3.1415927f);
                }
                if (pblipg->fTable == 2) {
                    pblip->ptable[index].a = av2[iblip];
                    pblip->ptable[index].b = apos2[iblip];
                }
                index++;
                pblip->pos2[index - 1] = pblip->pos[index - 1];
                pblip->vel2[index - 1] = pblip->vel[index - 1];
                pblip->row2[index - 1] = *prow;
                pblip->cblip++;
                pblipg->cblip++;
                iblip++;
                if (index >= 0x2B)
                    break;
            }
        }
        pblip = pblip->pblipNext;
    }
}
