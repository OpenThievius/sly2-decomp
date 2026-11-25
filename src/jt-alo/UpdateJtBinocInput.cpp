extern "C" int bevy_player_p15_binoc_active();
extern "C" int FButtonPressedWithin(void*, int, float);
extern "C" void StopBinoc(void*);
extern "C" void UpdateBinoc(void*);
#include "jt.h"
/* a JT with the one word of the Sly part this function reads: 0x1D40 (the player's mode) */
struct JT_1D40 : JT { u8 unknown_0x1320[0x1D40 - 0x1320]; int mode; };
extern "C" void UpdateJtBinocInput(JT_1D40* jt)
{
    if (bevy_player_p15_binoc_active()) {
        void* binoc = jt->PvBinoc();
        if (jt->binocState == 1 && jt->binocPhase == 0) {
            int buttons = (jt->mode == 7) ? 0x410 : 0x4F0;
            if (FButtonPressedWithin(jt->pjoy, buttons, 0.25f)) StopBinoc(binoc);
        }
        UpdateBinoc(binoc);
    }
}
