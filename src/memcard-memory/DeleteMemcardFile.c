/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "memcard.h"

s32 McSync(MEMCARD *pmc, s32 nStart, s32 nFuncNo, s32 *pnResult);
s32 sceMcDelete(s32 port, s32 slot, const char *name);

s32 DeleteMemcardFile(SAVE *psave, const char *name) {
    s32 nError;

    nError = McSync(&psave->mc, sceMcDelete(psave->port, psave->slot, name), 0xF, 0);
    return ((nError ^ 0xE) == 0) ? 0 : nError;
}
