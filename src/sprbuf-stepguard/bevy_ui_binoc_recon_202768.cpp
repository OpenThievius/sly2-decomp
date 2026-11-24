#include "blot.h"

/* A recon target: RECON, an ALO subclass (class 46, 0x120 bytes; sprbuf_stepguard_202d38.cpp). */
struct RECON : LO {
    u8 unknown_0x50[0x9C];
    /* 0xEC */ void *ptask;
    u8 unknown_0xF0[0x4];
    /* 0xF4 */ s32 field_0xF4;      /* the binocular state 7 copies it to BINOCRECON::field_0xBC */
    u8 unknown_0xF8[0x4];
    /* 0xFC */ s32 stream;          /* the stream (-1: none) and wipe argument the binocular state 9 starts */
};

/* The binocular recon screen (the bevy_ui_binoc_recon functions): its state, the recon targets and the two blots it shows. */
struct BINOCRECON {
    /* 0x0 */ s32 state;
    u8 unknown_0x4[0x70];
    /* 0x74 */ s32 clist;           /* the targets listed on the screen (bevy_ui_binoc_recon_202030) */
    u8 unknown_0x78[0x14];
    /* 0x8C */ RECON *precon;       /* the target being looked at */
    u8 unknown_0x90[0x10];
    /* 0xA0 */ s32 grfSaved;        /* state 8 saves the focus object's flags here and puts them back when it leaves */
    /* 0xA4 */ s32 wipe;
    /* 0xA8 */ LO **pplo;           /* the focus object */
    /* 0xAC */ BLOT *pblotA;
    /* 0xB0 */ BLOT *pblotB;
    u8 unknown_0xB4[0x8];
    /* 0xBC */ s32 field_0xBC;
    /* 0xC0 */ s32 field_0xC0;
};

/* the field pblotB's subclass of BLOT keeps at 0xF4: the target it shows */
struct RECONBLOTVIEW {
    u8 unknown_0x0[0xF4];
    /* 0xF4 */ RECON *precon;
};

extern "C" {
void ClearHandsOff(void *, int);
int ClearReconVisibility(BINOCRECON *, int);
void HideReconLinks(BINOCRECON *);
int NewEmitter(int, int);
void SeekBlotLabel(BLOT *, int, float);
void SetBlotBlots(BLOT *, int);
void SetBlotModal(BLOT *, int);
void SetClockRate(void *, int, float);
void SetEmitterUnpositioned(int, int);
void SetHandsOff(void *, int);
void SetReconTargetDone(RECON *, int);
float SetTimerTimers__FP5TIMER6TIMERS(BLOT *, int);
void ShowReconLinks(BINOCRECON *);
int StartStream(void *, int, int);
void StartWipe(int, int, int);
void UpdateReconLinkFades(BINOCRECON *);
void bevy_camera_follow_activity(void *, int, int);
void bevy_ui_binoc_recon_201f90(BINOCRECON *);
int bevy_ui_binoc_recon_202030(BINOCRECON *);
void bevy_ui_binoc_recon_2021f8(BINOCRECON *);
int bevy_ui_binoc_recon_2022d8(BINOCRECON *);
void func_0014FE28(void *);
int func_001FE5B8(void *, int, int);
void func_00213928(BLOT *, int);
void func_00213B00(BLOT *, int);
extern char B_002DE390;
extern char B_002DEB30;
extern char B_003DD040;
extern char B_003DD490;
extern char g_2dded0;
static inline int GrfOf(LO *plo)
{
    int grf = plo->grfSw;
    if (!(grf & 1))
        return *(int *)grf;
    return grf;
}
static inline void AddGrf(LO *plo, int bits)
{
    int grf = plo->grfSw;
    if (((grf ^ 1) & 1) != 0)
        *(int *)grf |= bits;
    else
        plo->grfSw = grf | bits;
}
void bevy_ui_binoc_recon_202768(BINOCRECON *arg0, int arg1) {
    int old = arg0->state;
    if ((old != arg1) && (arg0->pblotA != 0) && (arg0->pblotB != 0)) {
        int newIsRecon = (unsigned int)(arg1 - 8) < 2U;
        if (((unsigned int)(old - 8) < 2U) != newIsRecon) {
            if (newIsRecon != 0) {
                SetHandsOff(&B_003DD490, 0);
            } else {
                ClearHandsOff(&B_003DD490, 0);
            }
        }
        switch (arg0->state) {
        case -1:
        case 10:
            break;
        case 1:
            UpdateReconLinkFades(arg0);
            bevy_ui_binoc_recon_202030(arg0);
            func_00213B00(arg0->pblotA, 0x35D);
            if (arg0->clist > 0) {
                func_00213B00(arg0->pblotA, 0x35E);
            }
            bevy_ui_binoc_recon_2021f8(arg0);
            break;
        case 4:
            func_00213928(arg0->pblotB, 0x359);
            break;
        case 5:
        case 6:
            func_00213928(arg0->pblotB, 0x35A);
            break;
        case 7:
            func_00213928(arg0->pblotA, 0x356);
            func_00213928(arg0->pblotB, 0x356);
            func_00213928(arg0->pblotB, 0x357);
            break;
        case 8: {
            LO *holder = *arg0->pplo;
            int tagged = holder->grfSw;
            int saved = arg0->grfSaved;
            if (!(tagged & 1)) {
                *(int *)tagged = saved | (*(int *)tagged & 1);
            } else {
                holder->grfSw = saved | (tagged & 1);
            }
            SetClockRate(&g_2dded0, 0, 1.0f);
            func_001FE5B8(&B_003DD040, 1, 1);
            func_00213928(arg0->pblotA, 0x358);
            break;
        }
        case 9:
            func_0014FE28(&B_002DE390);
            SetBlotModal(arg0->pblotA, -1);
            arg0->pblotA->Select(0x310);
            if (arg0->wipe != 0) {
                int stream = arg0->precon->stream;
                if (stream != -1) {
                    StartStream(&B_003DD040, stream, 0);
                }
                StartWipe(arg0->wipe, 0x608, arg0->precon->stream);
            }
            SetReconTargetDone(arg0->precon, 1);
            bevy_camera_follow_activity(&B_002DEB30, 0xA, 0);
            arg0->precon = 0;
            if (bevy_ui_binoc_recon_2022d8(arg0) != 0) {
                func_00213B00(arg0->pblotA, 0x35D);
                if (arg0->clist > 0) {
                    func_00213B00(arg0->pblotA, 0x35E);
                }
            }
            bevy_ui_binoc_recon_2021f8(arg0);
            break;
        }
        int previous = arg0->state;
        arg0->state = arg1;
        switch (arg1) {
        case 0:
            arg0->field_0xBC = -1;
            arg0->precon = 0;
            arg0->field_0xC0 = -1;
            ClearReconVisibility(arg0, previous);
            arg0->pblotA->Select(-1);
            HideReconLinks(arg0);
            bevy_ui_binoc_recon_201f90(arg0);
            bevy_camera_follow_activity(&B_002DEB30, 9, 0);
            return;
        case 1:
            func_00213928(arg0->pblotA, 0x35D);
            arg0->pblotB->Select(0x339);
            return;
        case 5:
            func_00213B00(arg0->pblotB, 0x35A);
            SeekBlotLabel(arg0->pblotB, 0x35A, 0.0f);
            return;
        case 6:
            func_00213B00(arg0->pblotB, 0x35A);
            SeekBlotLabel(arg0->pblotB, 0x35A, 0.0f);
            return;
        case 7:
            SetEmitterUnpositioned(NewEmitter(0x52, previous), 0);
            arg0->field_0xBC = arg0->precon->field_0xF4;
            func_00213B00(arg0->pblotA, 0x356);
            func_00213B00(arg0->pblotB, 0x356);
            func_00213B00(arg0->pblotB, 0x357);
            return;
        case 8: {
            func_00213928(arg0->pblotA, 0x35B);
            func_00213B00(arg0->pblotA, 0x358);
            LO **handle = arg0->pplo;
            arg0->grfSaved = GrfOf(*handle) & ~1;
            AddGrf(*handle, 0x102);
            func_001FE5B8(&B_003DD040, 1, 0);
            SetClockRate(&g_2dded0, 0, 0.0f);
            return;
        }
        case 9:
            arg0->pblotB->Select(0x339);
            arg0->pblotA->Select(0x35C);
            SetBlotModal(arg0->pblotA, 0);
            return;
        case 3:
        case 4:
            ((RECONBLOTVIEW *)arg0->pblotB)->precon = arg0->precon;
            arg0->pblotB->Select(0x337);
            func_00213B00(arg0->pblotB, 0x359);
            SeekBlotLabel(arg0->pblotB, 0x359, 0.0f);
            return;
        case 2:
            arg0->pblotB->Select(0x339);
            return;
        case 10:
            arg0->field_0xBC = -1;
            arg0->precon = 0;
            arg0->field_0xC0 = -1;
            arg0->pblotB->Hide();
            arg0->pblotA->Hide();
            ShowReconLinks(arg0);
            bevy_camera_follow_activity(&B_002DEB30, 0xB, 0);
            return;
        case -1:
            if (previous != 0xA) {
                bevy_camera_follow_activity(&B_002DEB30, 0xB, 0);
                BLOT *first = arg0->pblotA;
                if (first->blots != 0) {
                    SetBlotBlots(first, 1);
                    SetTimerTimers__FP5TIMER6TIMERS(arg0->pblotA, 1);
                }
                BLOT *second = arg0->pblotB;
                if (second->blots != 0) {
                    SetBlotBlots(second, 1);
                    SetTimerTimers__FP5TIMER6TIMERS(arg0->pblotB, 1);
                }
            }
            break;
        }
    }
}
}
