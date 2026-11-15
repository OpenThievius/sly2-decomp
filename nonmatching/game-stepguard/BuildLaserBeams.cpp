// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "alloc.h"
#include "ps2inline.h"
#include "vu0inline.h"

struct LO;
struct SWX;
struct CRV;
struct CRVVT {
    char pad[0xF8];
    short delta;
    short pad2;
    MATRIX4 *(*pfnGetMatrix)(CRV *);
};
struct CRV {
    char pad0[0xC];
    CRVVT *pvt;
    char pad10[0xE8 - 0x10];
    int ccv;
    char padEC[8];
    QW *apos;
};
struct SEG { float s, v, a, dt, t; };
struct PATHPARAMS { float u, speed, period; int mode; };
struct PATHSTATE { PATHPARAMS params; float sAccel, sDecel; };
struct LASEREND {
    int oid;
    int kind;
    int pad8[2];
    union {
        QW pos;
        struct {
            CRV *pcrv;
            float s;
            union {
                PATHPARAMS params;
                struct {
                    int cseg;
                    SEG aseg[6];
                    int iseg;
                };
            };
        };
    };
};
struct LASERBEAM { LASEREND aend[2]; char pad[0x10]; };
struct GEOM { int cpos; QW *apos; char pad[0x10]; };
struct LASERSO {
    int xf;
    struct LASER *plaser;
    int pad8;
    int field0C;
    u64 grf;
    char pad18[0x78 - 0x18];
    GEOM geomLocal;
    GEOM geomWorld;
};
struct LASER {
    char pad0[0x18];
    int field18;
    char pad1C[0x28 - 0x1C];
    u64 grfSo;
    char pad30[0x40 - 0x30];
    u32 flags;
    char pad44[0x60 - 0x44];
    int xf;
    char pad64[0xE0 - 0x64];
    int fHasSo;
    LASERSO *pso;
    char padE8[0x198 - 0xE8];
    int cbeam;
    LASERBEAM *abeam;
};

extern "C" {
void RemoveSoGeomsFromOxa(LASER *plaser);
void AddSoGeomsToOxa(LASER *plaser);
LO *PloFindSwObject_thunk(SWX *psw, int grffso, int oid, LASER *plaser);
int FIsBasicDerivedFrom(LO *plo, int cid);
float SMaxCrv(LO *plo);
void GetPathPosFromS(LO *plo, QW *ppos, void *pv, float s);
QW PosLoWorld(void *plo);
QW ConvertXfPos(int grfxf, int xf, QW pos);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *preq);
void CloneGeom(GEOM *pgeomSrc, void *pv, GEOM *pgeomDst);
void *memset(void *pv, int b, unsigned int cb);
extern SWX B_003DD490;
extern float D_FLT_002C3610;
extern const QW RO_002A2DF0;
extern const QW RO_002A2E00;
}

static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}

static inline void StartLinearSeg(SEG *pseg, int fReverse, float sMax, PATHPARAMS *pparams)
{
    if (fReverse) {
        pseg->s = sMax;
        pseg->v = -pparams->speed;
        pseg->t = (1.0f - pparams->u) * pparams->period;
    } else {
        pseg->v = pparams->speed;
        pseg->t = pparams->u * pparams->period;
    }
}

extern "C" void BuildLaserBeams(LASER *plaser)
{
    QW posMin;
    QW posMax;
    RemoveSoGeomsFromOxa(plaser);
    posMin = RO_002A2DF0;
    posMax = RO_002A2E00;
    for (int ibeam = 0; ibeam < plaser->cbeam; ibeam++) {
        LASERBEAM *pbeam = &plaser->abeam[ibeam];
        for (u32 iend = 0; iend < 2; iend++) {
            LASEREND *pend = &pbeam->aend[iend];
            pend->kind = -1;
            if (pend->oid != -1) {
                LO *plo = PloFindSwObject_thunk(&B_003DD490, 1, pend->oid, plaser);
                if (plo != 0) {
                    if (FIsBasicDerivedFrom(plo, 0xA) != 0) {
                        PATHSTATE state;
                        state.params = pend->params;
                        int fReverse = 0;
                        state.params.u = GClamp(state.params.u, 0.0f, 1.0f);
                        if (state.params.speed < 0.0f) {
                            fReverse = 1;
                            state.params.speed = -state.params.speed;
                        }
                        state.params.period = __builtin_fabsf(state.params.period);
                        if (state.params.mode != 8 && state.params.mode != 0x10 && state.params.mode != 0)
                            state.params.mode = 8;
                        float sMax = SMaxCrv(plo);
                        if (0.0f < state.params.period)
                            state.params.speed = sMax / state.params.period;
                        else if (0.0f < state.params.speed)
                            state.params.period = sMax / state.params.speed;
                        float s = state.params.u * sMax;
                        if (state.params.speed == 0.0f || state.params.period == 0.0f) {
                            pend->kind = 0;
                            GetPathPosFromS(plo, &pend->pos, 0, s);
                        } else {
                            pend->pcrv = (CRV *)plo;
                            pend->kind = 1;
                            pend->s = s;
                            SEG *aseg = pend->aseg;
                            memset(aseg, 0, sizeof(pend->aseg));
                            switch (state.params.mode) {
                            case 8:
                                pend->cseg = 1;
                                StartLinearSeg(aseg, fReverse, sMax, &state.params);
                                aseg->dt = state.params.period;
                                pend->iseg = 0;
                                break;
                            case 0: {
                                pend->cseg = 2;
                                StartLinearSeg(aseg, fReverse, sMax, &state.params);
                                aseg->dt = state.params.period;
                                SEG *pseg = &pend->aseg[1];
                                pseg->s = fReverse ? 0.0f : sMax;
                                pseg->t = 0.0f;
                                pseg->v = 0.0f;
                                pend->iseg = 0;
                                break;
                            }
                            case 0x10: {
                                if (D_FLT_002C3610 * 3.0f <= sMax)
                                    state.sAccel = D_FLT_002C3610;
                                else
                                    state.sAccel = sMax * 0.2f;
                                float sAccel2 = state.sAccel + state.sAccel;
                                state.sDecel = sMax - state.sAccel;
                                float dtAccel = sAccel2 * state.params.period / (sMax + sAccel2);
                                float dtCruise = state.params.period - (dtAccel + dtAccel);
                                state.params.speed = (sMax - sAccel2) / dtCruise;
                                float accel = state.params.speed * state.params.speed / sAccel2;
                                pend->cseg = 6;
                                SEG *pseg = aseg;
                                pseg->dt = dtAccel;
                                pseg->a = accel;
                                pseg = &pend->aseg[1];
                                pseg->s = state.sAccel;
                                pseg->dt = dtCruise;
                                pseg->v = state.params.speed;
                                pseg = &pend->aseg[2];
                                pseg->s = state.sDecel;
                                pseg->dt = dtAccel;
                                pseg->v = state.params.speed;
                                pseg->a = -accel;
                                pseg = &pend->aseg[3];
                                pseg->s = sMax;
                                pseg->dt = dtAccel;
                                pseg->a = -accel;
                                pseg = &pend->aseg[4];
                                pseg->s = state.sDecel;
                                pseg->dt = dtCruise;
                                pseg->v = -state.params.speed;
                                pseg = &pend->aseg[5];
                                pseg->s = state.sAccel;
                                pseg->dt = dtAccel;
                                pseg->a = accel;
                                pseg->v = -state.params.speed;
                                pend->iseg = 0;
                                do {
                                    pseg = &pend->aseg[pend->iseg];
                                    SEG *psegNext = pseg + 1;
                                    if (s < psegNext->s) {
                                        float t = (s - pseg->s) * 2.0f / (pseg->v + psegNext->v);
                                        if (fReverse) {
                                            pend->iseg = 5 - pend->iseg;
                                            pseg = &pend->aseg[pend->iseg];
                                            pseg->t = pseg->dt - t;
                                        } else {
                                            pseg->t = t;
                                        }
                                        break;
                                    }
                                } while (++pend->iseg < 3);
                                break;
                            }
                            }
                            u32 flags = plaser->flags;
                            if ((flags ^ 1) & 1)
                                *(u32 *)flags |= 2;
                            else
                                plaser->flags = flags | 2;
                        }
                    } else if (FIsBasicDerivedFrom(plo, 3) != 0 || FIsBasicDerivedFrom(plo, 0x30) != 0) {
                        pend->kind = 0;
                        pend->pos = PosLoWorld(plo);
                    }
                }
            }
            if (pend->kind == -1) {
                pend->kind = 0;
                pend->pos = PosLoWorld(plaser);
            }
            switch (pend->kind) {
            case 0: {
                QW pos = pend->pos;
                posMin = VectorMiniXyz(posMin, pos);
                posMax = VectorMaxXyz(posMax, pos);
                pend->pos = ConvertXfPos(0, plaser->xf, pos);
                break;
            }
            case 1: {
                CRV *pcrv = pend->pcrv;
                MATRIX4 mat = *pcrv->pvt->pfnGetMatrix((CRV *)(pcrv->pvt->delta + (char *)pcrv));
                pcrv = pend->pcrv;
                for (int icv = 0; icv < pcrv->ccv; icv++) {
                    QW pos = TransformPoint(pcrv->apos[icv], mat.row[0], mat.row[1], mat.row[2], mat.row[3]);
                    posMin = VectorMiniXyz(posMin, pos);
                    posMax = VectorMaxXyz(posMax, pos);
                    pcrv = pend->pcrv;
                }
                break;
            }
            }
        }
    }
    if (plaser->cbeam != 0) {
        ALLOCREQ allocreq;
        plaser->fHasSo = 1;
        allocreq.cb = 0xB0;
        allocreq.cbAlign = 0x10;
        LASERSO *pso = (LASERSO *)PvAllocSwClearImpl__Fi(&allocreq);
        plaser->pso = pso;
        pso->xf = plaser->xf;
        pso->plaser = plaser;
        pso->geomLocal.cpos = 2;
        pso->field0C = plaser->field18;
        pso->grf |= 0x8000L << 33;
        allocreq.cbAlign = 0x10;
        allocreq.cb = 0x20;
        pso->geomLocal.apos = (QW *)PvAllocSwClearImpl__Fi(&allocreq);
        CloneGeom(&pso->geomLocal, 0, &pso->geomWorld);
        pso->geomWorld.apos[0] = posMin;
        pso->geomWorld.apos[1] = posMax;
        pso->geomLocal.apos[0] = ConvertXfPos(0, plaser->xf, posMin);
        pso->geomLocal.apos[1] = ConvertXfPos(0, plaser->xf, posMax);
    }
    if ((int)(plaser->grfSo >> 60) & 1)
        AddSoGeomsToOxa(plaser);
}
