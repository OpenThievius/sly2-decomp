// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
// bevy_ui_binoc_recon_202d38: per-frame update of the binocucom recon mode.
// Behaviour: projects the current target (and a point above it, offset by g_2ddfa0[1] * target radius)
// to screen space (x * 320 + 320, y * -246.4 + 246.4); fCenter = clamp(1 - (|screen - center|.xy - 128) / 128, 0, 1)
// at +0x90, fSize = |top - screen|.xy / 120 at +0x94 (folded to 2 - fSize and flag +0x98 cleared when > 1),
// then runs the recon state machine (state at +0, -1..10) through bevy_ui_binoc_recon_202768.
struct TARGET {
    char pad0[0xE4];
    float rRadius;
    float fDone;
    struct TGTINFO *pinfo;
    char padF0[0x108 - 0xF0];
    int kind;
    int fAlt;
    int labelAlt;
};
struct TGTINFO { char pad[0x54]; int state; };
struct BLOT { char pad[0x110]; int alabel[5]; };
struct BINOC { char pad[0x20]; int mode; };
struct RECON {
    int state;
    char pad4[0x10 - 4];
    QW posCenter;
    char pad20[0x30 - 0x20];
    int ctarget;
    TARGET *atarget[0x16];
    TARGET *ptarget;
    float fCenter;
    float fSize;
    int fSmall;
    float tLabel;
    char padA0[0xA8 - 0xA0];
    BINOC *pbinoc;
    BLOT *pblot;
    BLOT *pblotB0;
    int fStop;
    char padB8[0xC0 - 0xB8];
    int label;
};
struct JOY { char pad[0x150]; void *pjoy; };
extern float g_2dded0;
extern QW g_2ddfa0[2];
extern char B_002DE2E0[];
extern JOY *g_2e1e40;
extern "C" {
void StopBinoc(BINOC *);
void PickReconTarget(RECON *);
void UpdateReconLinkFades(RECON *);
int bevy_ui_binoc_recon_2022d8(RECON *);
void func_00213928(BLOT *, int);
void func_00213B00(BLOT *, int);
int FBlotLabelPlaying(BLOT *, int);
void SeekBlotLabel(BLOT *, int, float);
int FReconTargetDone(TARGET *);
int FActiveCplcy(char *);
int FButtonPressedWithin(void *, int, float);
}
void bevy_ui_binoc_recon_202768(RECON *, int);
QW PosLoWorld(TARGET *);
QW ConvertCmWorldToScreen(QW *, QW);

union VU_SCALE { QW q; VECTOR v; };

void bevy_ui_binoc_recon_202d38(RECON *precon)
{
    VU_SCALE scale;

    if (precon->pblot == 0 || precon->pblotB0 == 0)
        return;
    if (precon->fStop != 0) {
        precon->fStop = 0;
        StopBinoc(precon->pbinoc);
    }
    if (precon->tLabel + 5.0f < g_2dded0)
        func_00213928(precon->pblot, 0x35B);
    if (precon->state < 8) {
        if (precon->state >= 2) {
            PickReconTarget(precon);
            UpdateReconLinkFades(precon);
            if (bevy_ui_binoc_recon_2022d8(precon) == 0)
                bevy_ui_binoc_recon_202768(precon, 1);
        }
    }
    if (precon->ptarget != 0) {
        QW pos = PosLoWorld(precon->ptarget);
        QW *pcm = g_2ddfa0;
        scale.q = VectorFromWord(*(u32 *)&precon->ptarget->rRadius);
        QW posTop = VectorAdd(pos, VectorScaleX(pcm[1], scale.q));
        pcm -= 6;
        QW scr = ConvertCmWorldToScreen(pcm, pos);
        QW scrTop = ConvertCmWorldToScreen(pcm, posTop);
        float x = LaneX(scr) * 320.0f + 320.0f;
        float y = LaneX(RotateWords3(scr)) * -246.40001f + 246.40001f;
        float z = FloatFromWord(LaneWordZ(scr));
        scale.q = JoinLowDoublewords(z, InterleaveLowWords(y, x));
        float xTop = LaneX(scrTop) * 320.0f + 320.0f;
        float yTop = LaneX(RotateWords3(scrTop)) * -246.40001f + 246.40001f;
        float zTop = FloatFromWord(LaneWordZ(scrTop));
        QW top = JoinLowDoublewords(zTop, InterleaveLowWords(yTop, xTop));
        float dCenter = LaneX(SqrtX(SquaredLengthXy(VectorSub(scale.q, precon->posCenter))));
        float fCenter = 1.0f - (dCenter - 128.0f) * 0.0078125f;
        float fSize = LaneX(SqrtX(SquaredLengthXy(VectorSub(scale.q, top)))) * 0.008333334f;
        scale.q = top;
        precon->fCenter = 0.0f > fCenter ? 0.0f : fCenter;
        fCenter = fCenter < 1.0f ? fCenter : 1.0f;
        precon->fSize = fSize;
        precon->fSmall = 1;
        if (1.0f < fSize) {
            precon->fSmall = 0;
            precon->fSize = 2.0f - fSize;
        }
        precon->fSize = precon->fSize > 0.0f ? precon->fSize : 0.0f;
    }
    switch (precon->state) {
    case 2:
        if (precon->ptarget != 0 && precon->ptarget->kind != 2)
            bevy_ui_binoc_recon_202768(precon, 4);
        break;
    case 4:
        if (precon->ptarget == 0)
            bevy_ui_binoc_recon_202768(precon, 2);
        else if (precon->ptarget->kind == 3)
            bevy_ui_binoc_recon_202768(precon, 3);
        else if (1.0f <= precon->fCenter) {
            if (precon->fSmall)
                bevy_ui_binoc_recon_202768(precon, 5);
            else
                bevy_ui_binoc_recon_202768(precon, 6);
        }
        break;
    case 3:
        if (precon->ptarget == 0)
            bevy_ui_binoc_recon_202768(precon, 2);
        else if (precon->ptarget->kind != 3)
            bevy_ui_binoc_recon_202768(precon, 4);
        break;
    case 5:
        if (precon->ptarget == 0)
            bevy_ui_binoc_recon_202768(precon, 2);
        else if (precon->fCenter < 1.0f)
            bevy_ui_binoc_recon_202768(precon, 4);
        else if (1.0f - precon->ptarget->fDone <= precon->fSize)
            bevy_ui_binoc_recon_202768(precon, 7);
        else
            SeekBlotLabel(precon->pblotB0, 0x35A, precon->fSize);
        break;
    case 6:
        if (precon->ptarget == 0)
            bevy_ui_binoc_recon_202768(precon, 2);
        else if (precon->fCenter < 1.0f)
            bevy_ui_binoc_recon_202768(precon, 4);
        else if (1.0f - precon->ptarget->fDone <= precon->fSize)
            bevy_ui_binoc_recon_202768(precon, 7);
        else
            SeekBlotLabel(precon->pblotB0, 0x35A, precon->fSize);
        break;
    case 7:
        if (precon->ptarget != 0) {
            if (precon->fCenter < 1.0f || precon->fSize < 1.0f - precon->ptarget->fDone) {
                if (precon->fSmall)
                    bevy_ui_binoc_recon_202768(precon, 5);
                else
                    bevy_ui_binoc_recon_202768(precon, 6);
            }
        } else {
            bevy_ui_binoc_recon_202768(precon, 2);
        }
        break;
    case 8: {
        if (FBlotLabelPlaying(precon->pblot, 0x358))
            break;
        TARGET *ptarget = precon->ptarget;
        int fSet = 0;
        if (ptarget != 0 && ptarget->kind == 1 && 1.0f <= precon->fCenter && 1.0f - ptarget->fDone <= precon->fSize) {
            if (ptarget->fAlt == 0) {
                bevy_ui_binoc_recon_202768(precon, 9);
            } else {
                precon->label = ptarget->labelAlt;
                fSet = 1;
                bevy_ui_binoc_recon_202768(precon, 7);
            }
        } else if (ptarget != 0 && ptarget->kind != 1) {
            precon->label = precon->pblot->alabel[0];
            bevy_ui_binoc_recon_202768(precon, 3);
            fSet = 1;
        } else if (1.0f <= precon->fCenter && precon->fSmall != 0) {
            precon->label = precon->pblot->alabel[1];
            bevy_ui_binoc_recon_202768(precon, 5);
            fSet = 1;
        } else if (1.0f <= precon->fCenter && precon->fSmall == 0) {
            precon->label = precon->pblot->alabel[2];
            bevy_ui_binoc_recon_202768(precon, 6);
            fSet = 1;
        } else if (ptarget != 0) {
            precon->label = precon->pblot->alabel[3];
            bevy_ui_binoc_recon_202768(precon, 4);
            fSet = 1;
        } else {
            precon->label = precon->pblot->alabel[4];
            bevy_ui_binoc_recon_202768(precon, 2);
            fSet = 1;
        }
        if (fSet) {
            func_00213B00(precon->pblot, 0x35B);
            precon->tLabel = g_2dded0;
        }
        break;
    }
    case 9: {
        if (FBlotLabelPlaying(precon->pblot, 0x35C))
            break;
        bevy_ui_binoc_recon_202768(precon, 2);
        int fAll = 1;
        for (int i = 0; i < precon->ctarget; i++) {
            TARGET *ptarget = precon->atarget[i];
            int fDone = FReconTargetDone(ptarget);
            int fIdle = ptarget->pinfo == 0 || ptarget->pinfo->state == 1;
            if (!fDone && fIdle) {
                fAll = 0;
                break;
            }
        }
        if (fAll)
            precon->fStop = 1;
        break;
    }
    case 10:
        if (!FBlotLabelPlaying(precon->pblot, 0x314))
            bevy_ui_binoc_recon_202768(precon, -1);
        break;
    case 0:
        if (FBlotLabelPlaying(precon->pblot, 0x314))
            bevy_ui_binoc_recon_202768(precon, 1);
        break;
    case 1:
        UpdateReconLinkFades(precon);
        if (bevy_ui_binoc_recon_2022d8(precon))
            bevy_ui_binoc_recon_202768(precon, 2);
        break;
    case -1:
        break;
    }
    if (precon->pbinoc->mode == 1)
        return;
    switch (precon->state) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        if (!FActiveCplcy(B_002DE2E0) && FButtonPressedWithin(g_2e1e40->pjoy, 0xA, 0.0f))
            bevy_ui_binoc_recon_202768(precon, 8);
        break;
    case 7:
        if (!FActiveCplcy(B_002DE2E0) && FButtonPressedWithin(g_2e1e40->pjoy, 0xFA, 0.0f))
            bevy_ui_binoc_recon_202768(precon, 8);
        break;
    }
}
