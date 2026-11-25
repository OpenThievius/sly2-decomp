#include "murray.h"
extern "C" int FButtonPressedWithin(JOY *, int, float);
extern "C" int StopBinoc(void *);
extern "C" void UpdateBinoc(void *);
extern "C" int bevy_player_p15_binoc_active();

extern "C" void UpdateMurrayBinoc(MURRAY *obj) {
    if (bevy_player_p15_binoc_active() != 0) {
        void *binoc = obj->PvBinoc();
        if (obj->binocState == 1 && obj->binocPhase == 0 &&
            FButtonPressedWithin(obj->pjoy, 0x4F0, 0.25f) != 0) {
            StopBinoc(binoc);
        }
        UpdateBinoc(binoc);
    }
}
