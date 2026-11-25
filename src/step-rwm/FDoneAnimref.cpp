// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
#include "sma.h"
extern "C" {
int FAsegaGone(ASEGA *);
int FSmaRetracted(SMA *);
int FJumperDone(JUMPER *);
int func_0020CA98(void *);
}

int FDoneAnimref(ANIMREF *ref)
{
    int result;
    switch (ref->kind) {
    case 0:
        result = 0;
        if (ref->pinst != 0) { if (!FAsegaGone((ASEGA *)ref->pinst)) goto out; }
        result = 1;
        break;
    case 1:
        result = 0;
        if (ref->pinst != 0) {
            if (!FSmaRetracted((SMA *)ref->pinst)) { if (((SMA *)ref->pinst)->pasega != 0) goto out; }
        }
        result = 1;
        break;
    case 2:
        result = 0;
        if (ref->pinst != 0) { if (!FJumperDone((JUMPER *)ref->pinst)) goto out; }
        result = 1;
        break;
    case 3:
        result = 0;
        if (ref->pinst != 0) { if (!func_0020CA98(ref->pinst)) goto out; }
        result = 1;
        break;
    case -1:
    default:
        result = 1;
    }
out:
    return result;
}
