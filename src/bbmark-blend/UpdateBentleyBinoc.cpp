// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
#include "joy.h"
/* the binoculars part InitJt starts at 0xF00 (JT::PvBinoc()): its own functions take its address, their layout is local to them */
struct BINOC;
extern "C" {
s32 FButtonPressedWithin(JOY *, s32, f32);
void StopBinoc(BINOC *);
void UpdateBinoc(BINOC *);
s32 bevy_player_p15_binoc_active(BENTLEY *);

void UpdateBentleyBinoc(BENTLEY *pbentley) {
    BINOC *pbinoc;

    if (bevy_player_p15_binoc_active(pbentley) != 0) {
        pbinoc = (BINOC *)pbentley->PvBinoc();
        if ((pbentley->binocState == 1) && (pbentley->binocPhase == 0) && (FButtonPressedWithin(pbentley->pjoy, 0x4F0, 0.25f) != 0)) {
            StopBinoc(pbinoc);
        }
        UpdateBinoc(pbinoc);
    }
}

}
