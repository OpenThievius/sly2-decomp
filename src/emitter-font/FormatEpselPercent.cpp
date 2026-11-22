// SPDX-License-Identifier: GPL-3.0-or-later
#include "cref.h"
#include "sw.h"
struct TARGET { u8 unknown_0x0[0x110]; s32 iepisode; /* FormatEpselPercent, FormatEpselTime: indexes the world's per-episode save paths */ };
extern "C" SW B_003DD490;
extern "C" char B_003D4A60[];
extern "C" const int D_002BE2F8[];
extern "C" const char RO_002A5160[];
extern "C" CRef RefGetGameSaveValue(SAVEPATH *, void *);
extern "C" int FGadgetAcquired(int);
extern "C" int sprintf(char *, const char *, ...);

void FormatEpselPercent(char *out)
{
    TARGET *hero = B_003DD490.ptarget;
    if (hero) {
        SAVEPATH *key = B_003DD490.apsavepathEpisodePercent[hero->iepisode];
        if (key) {
            int count = RefGetGameSaveValue(key, B_003D4A60).m_tag.m_n;
            int percent = count * 95 / 100;
            TARGET *again = B_003DD490.ptarget;
            int acquired = FGadgetAcquired(D_002BE2F8[again->iepisode]);
            sprintf(out, RO_002A5160, acquired ? percent + 5 : percent);
        }
    }
}
