// SPDX-License-Identifier: GPL-3.0-or-later
#include "amb.h"
/* the sound bank manager (0x3DD040): hBank is the bank handle StartAmb hands to the driver */
struct SNDBANKS { u8 unknown_0x0[0xE8]; s32 hBank; };
/* a sound record: kind 2 is a looping voice that reports back through OnAmbVoiceStarted */
struct SFXREC { s32 kind; };
/* the play request func_00232320 and func_002322F0 take (0x30 bytes, cleared first) */
struct SNDPLAY {
    s32 hBank;
    u8 unknown_0x4[4];
    s32 vol;
    s32 pan;
    s16 isndrec;
    u8 unknown_0x12[0xE];
    s16 pitch;
    u8 unknown_0x22[6];
    u32 grf;
    u8 unknown_0x2C[4];
};
extern "C" {
SFXREC *func_001FD028(SNDBANKS *, s32 sfxid);
s16 func_001FD070(SNDBANKS *, SFXREC *);
void DeactivateAmb(AMB *);
void *memset(void *, int, unsigned);
void func_00232320(SNDPLAY *, void (*)(int, AMB *), AMB *);
void func_002322F0(SNDPLAY *);
void SetAmbGrf(AMB *, int, int);
void *PpoSwFocusBase(void *);
void func_001FEED0(SNDBANKS *);
void OnAmbVoiceStarted(int, AMB *);
extern SNDBANKS B_003DD040;
extern u8 B_003DD490[];
extern void *g_2f7900;
extern void *g_2dd5bc;
extern void *g_2e1e40;
}

void StartAmb(AMB *pamb)
{
    SFXREC *prec = func_001FD028(&B_003DD040, pamb->sfxid);
    if (prec == 0 || B_003DD040.hBank == 0) {
        SetAmbGrf(pamb, 0x1FFF, 0);
        return;
    }
    if (pamb->grf & 2) {
        DeactivateAmb(pamb);
        return;
    }
    SNDPLAY play;
    memset(&play, 0, 0x30);
    play.grf = 3;
    play.hBank = B_003DD040.hBank;
    play.isndrec = func_001FD070(&B_003DD040, prec);
    if (pamb->grf & 0x10) {
        play.grf |= 4;
        play.vol = (int)(pamb->volAudible * 1024.0f);
    }
    if (pamb->grf & 0x20) {
        play.grf |= 8;
        play.pan = pamb->pan;
    }
    if (pamb->grf & 0x40) {
        play.grf |= 0x10;
        play.pitch = (short)(int)(pamb->pitch * 1524.0f);
    }
    if (prec->kind == 2) {
        pamb->fPending = 1;
        pamb->AddRef();
        func_00232320(&play, OnAmbVoiceStarted, pamb);
        SetAmbGrf(pamb, 0x7F, 0);
    } else {
        func_002322F0(&play);
        SetAmbGrf(pamb, 0x1FFF, 0);
        void *speaker = 0;
        switch (pamb->sfxid) {
        case 0x6F: speaker = g_2e1e40; break;
        case 0x73: speaker = g_2dd5bc; break;
        case 0x15: speaker = g_2f7900; break;
        }
        if (speaker == PpoSwFocusBase(B_003DD490))
            func_001FEED0(&B_003DD040);
    }
}
