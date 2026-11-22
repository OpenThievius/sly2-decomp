// SPDX-License-Identifier: GPL-3.0-or-later
#include "dancer.h"
extern "C" {
void PostStepLoad();
}
void ResolveDancerMoves(DANCER *);

extern "C" void PostDancerLoad(DANCER *dancer) {
    PostStepLoad();
    ResolveDancerMoves(dancer);
    dancer->SetPlayable(0);
}
