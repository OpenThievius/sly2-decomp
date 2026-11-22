// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
#include "sw.h"
struct TARGET { u8 unknown_0x0[0x110]; s32 iepisode; /* FormatEpselPercent, FormatEpselTime: indexes the world's per-episode save paths */ };
extern "C" SW B_003DD490;
extern "C" char B_003D4A60[];
extern "C" const char RO_002A5168[];
extern "C" CRef RefGetGameSaveValue(SAVEPATH *, void *);
extern "C" float fmodf(float, float);
extern "C" int sprintf(char *, const char *, ...);

void FormatEpselTime(char *out)
{
    TARGET *hero = B_003DD490.ptarget;
    if (hero) {
        SAVEPATH *key = B_003DD490.apsavepathEpisodeDt[hero->iepisode];
        if (key) {
            float seconds = RefGetGameSaveValue(key, B_003D4A60).m_tag.m_g;
            int whole = (int)(seconds * 0.00027777778f);
            int minutes = (int)(fmodf(seconds, 3600.0f) * 0.016666668f);
            sprintf(out, RO_002A5168, whole, minutes);
        }
    }
}
