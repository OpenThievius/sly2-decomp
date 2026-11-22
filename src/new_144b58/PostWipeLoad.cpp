// SPDX-License-Identifier: GPL-3.0-or-later
#include "wipe.h"
#include "soproperty.h"

extern "C" {
void PostSoLoad(SO *pso);
void SetSoProperties(SO *pso, int count, const SOPROPERTY *aproperty);
/* the wipe's two property entries (flags, key, offset: 0x158 and 0x15C), defined in src/data as words */
extern unsigned int D_002BD380[6];

void PostWipeLoad(WIPE *pwipe) {
    PostSoLoad(pwipe);
    SetSoProperties(pwipe, 2, (const SOPROPERTY *)D_002BD380);
    pwipe->wipes = -1;
    pwipe->Remove();
}
}
