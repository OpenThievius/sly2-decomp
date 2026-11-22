/* SPDX-License-Identifier: GPL-3.0-or-later */
/* AMB, an ambient sound emitter (0x70 bytes; NewEmitter allocates it, InitAmbBase and InitAmb build it). The local struct under
   this name in each sound source (a vtable pointer after pad[0xC], a different slice of fields each time) is replaced by this one.
   A field is here when a matched function reads it at that offset; readers listed. C++ only. */
#ifndef SLY2_AMB_H
#define SLY2_AMB_H
#include "types.h"
#include "dl.h"

struct LO;

struct AMBBASE {
    DLE dle;                            /* InitAmbBase clears both words; ActivateAmb appends the emitter to the active list (ibDle 0) */
    u8 unknown_0x8[4];
    /* 0xC: the vtable pointer */
    virtual void AddRef();              /*  1: StartAmb, ActivateAmb call it */
    virtual void Release();             /*  2: OnAmbVoiceStarted, OnAmbVoicePolled call it */
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual int Slot8();                /*  8: StartSwAmbSfx compares its result with 2 */
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15(int arg1);      /* 15: UpdateAmbPositional calls it with 0 when the audible volume leaves 0 and 1 when it falls to 0 */
};

struct AMB : AMBBASE {
    /* 0x10 */ f32 volume;              /* InitAmbBase sets 1.0; SetAmbVolume, UpdateAmb */
    /* 0x14 */ s32 pan;                 /* SetAmbPan (0 to 359 degrees); StartAmb */
    /* 0x18 */ f32 pitch;               /* StartAmb (x 1524); SetAmbPitch */
    /* 0x1C */ struct LO *palo;            /* UpdateAmbPositional tests its grfo bit 60; SetAmbPos, SetEmitterUnpositioned */
    /* 0x20 */ QW pos;                  /* UpdateAmbPositional converts it to world space; SetAmbPos */
    /* 0x30 */ f32 lmMin;               /* InitAmbBase sets 300.0; SetAmbRange; UpdateAmbPositional passes &lmMin to CalculateVolPan */
    /* 0x34 */ f32 lmMax;               /* InitAmbBase sets 3000.0; SetAmbRange */
    u8 unknown_0x38[8];
    /* 0x40 */ s32 voice;               /* OnAmbVoiceStarted sets it; ContinueAmbVoice, PauseAmbVoice, StopSound pass it to the sound driver */
    /* 0x44 */ f32 volAudible;          /* InitAmbBase sets 1.0; StartAmb (x 1024); UpdateAmbPositional */
    /* 0x48 */ f32 fadeSeconds;         /* StopSound: above 0 the stop fades out over it (x 240); StopAmb sets it */
    /* 0x4C */ u16 cRef;               /* AMB_AddRef (slot 1) increments it, AMB_Release (slot 2) decrements it and destroys the emitter at 0; StreamAmb_AddRef/StreamAmb_Release do the same on the stream class's slots */
    /* 0x4E */ s16 cPause;              /* PauseAmb */
    /* 0x50 */ u16 grf;                 /* SetAmbGrf; StartAmb, UpdateAmb */
    /* 0x52 */ s16 fPending;            /* OnAmbVoiceStarted clears it; StartAmb sets it, UpdateAmb */
    u8 unknown_0x54[0xC];
    /* 0x60 */ s32 sfxid;               /* InitAmb sets it; StartAmb */
    u8 unknown_0x64[4];
    /* 0x68 */ u64 played;              /* func_001FC878 adds the elapsed clock ticks while the emitter is unpaused and its start flag is clear */
};

#if defined(__mips__)
typedef char check_AMB_size[(sizeof(AMB) == 0x70) ? 1 : -1];
#endif
#endif
