// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "epsel.h"
extern char B_002E65E0;
extern "C" float g_2ddf0c;
extern "C" void TryAutosave(char *, int);
extern "C" void SetEpselHint(EPSEL *, int);
extern "C" void SetTimerTimers__FP5TIMER6TIMERS(EPSEL *, int);
extern "C" void SetBlotBlots(EPSEL *, int);
extern "C" int LabelFromEpselMode(EPSEL *);
extern "C" void SetEpselMode(EPSEL *pepsel, int mode, int sub)
{
    int modeOld = pepsel->mode;
    if (modeOld == mode && pepsel->sub == sub)
        return;
    switch (modeOld) {
    case 0:
        TryAutosave(&B_002E65E0, 1);
        break;
    case 4:
    case 6: {
        int episodeNext = pepsel->episodeNext;
        pepsel->episodeNext = -1;
        pepsel->episode = episodeNext;
        break;
    }
    case 2:
        SetEpselHint(pepsel, 0);
        break;
    }
    if (mode == 2) {
        SetEpselHint(pepsel, -1);
        SetEpselHint(pepsel, 0);
    }
    pepsel->field_0x74 = -1;
    pepsel->field_0x70 = -1;
    pepsel->field_0x78 = -1;
    SetTimerTimers__FP5TIMER6TIMERS(pepsel, 1);
    SetBlotBlots(pepsel, 1);
    pepsel->mode = mode;
    pepsel->sub = sub;
    pepsel->tMode = *(float *)&g_2ddf0c;
    int label = LabelFromEpselMode(pepsel);
    if (label != -1) {
        PAUSEBLOTVT *vt = pepsel->vt;
        vt->pfnSelect((char *)pepsel + vt->deltaSelect, label);
    }
}
