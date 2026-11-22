/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "guardscriptbeh.h"

s32 FGuardScriptDone(struct GUARDSCRIPTBEH *beh) {
    return beh->pcmd == 0;
}
