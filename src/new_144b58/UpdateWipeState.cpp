// SPDX-License-Identifier: GPL-3.0-or-later
#include "wipe.h"

extern "C" {
int FAsegaGone(ASEGA *pasega);
int FStreamPlaying(u8 *pstreams, int hstream);
void ReleaseAsegaHandle(ASEGA **ppasega);
void SetWipeState(WIPE *pwipe, int wipes);
extern u8 B_003DD040[];

void UpdateWipeState(WIPE *pwipe) {
    switch (pwipe->wipes) {
    case 0:
        SetWipeState(pwipe, 1);
        return;
    case 3:
        if (FStreamPlaying(B_003DD040, pwipe->hstream) == 0) {
            SetWipeState(pwipe, 2);
            return;
        }
        return;
    case 2:
        ASEGA *pasega = pwipe->pasega;
        if ((pasega == 0) || (FAsegaGone(pasega) != 0)) {
            ReleaseAsegaHandle(&pwipe->pasega);
            SetWipeState(pwipe, -1);
        }
        break;
    }
}
}
