#include "amb.h"
extern "C" {
void SetAmbGrf(void *, s32, s32);
void snd_SoundIsStillPlaying_CB(s32, void *, void *);
extern char OnAmbVoicePolled;
void PollAmb(AMB *arg0) {
    if (arg0->grf & 0x400) {
        arg0->AddRef();
        snd_SoundIsStillPlaying_CB(arg0->voice, &OnAmbVoicePolled, arg0);
        SetAmbGrf(arg0, 0x400, 0);
    }
}
}
