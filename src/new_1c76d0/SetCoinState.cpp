// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
#include "coin.h"
extern "C" {
float GRandInRange(float, float);
CRef func_001D8A38(const char *first, ...);
CRef func_001D8B20(const CRef &value, const char *first, ...);
int sprintf(char *, const char *, ...);
void SetDprizeDprizes(DPRIZE *, int);
extern const char RO_002A7768[];
extern const char RO_002A7770[];
extern const char RO_002A7778[];
}

void SetCoinState(COIN *coin, int state)
{
    if (coin->dprizes == state) return;
    switch (state) {
    case 0:
        coin->wait = GRandInRange(coin->waitMin, coin->waitMax);
        break;
    case 1: {
        CRef ref;
        char name[0x10];
        ref.m_tagk = TAGK_Nil;
        sprintf(name, RO_002A7768, coin->cur->lootkc);
        ref = func_001D8A38(RO_002A7770, RO_002A7778, name, 0);
        func_001D8B20(CRef(ref.m_tag.m_n + 1, TAGK_S32), RO_002A7770, RO_002A7778, name, 0);
        MSGSINK *psink = (MSGSINK *)coin->aoidploB[1].plo;
        if (psink) {
            SINKMSG notice;
            notice.aw[0] = state;
            notice.aw[1] = (int)coin;
            psink->Notify(notice.aw);
        }
        state = 2;
        coin->HandleSpliceEvent(5, 0, 0, 0, 0);
        break;
    }
    }
    SetDprizeDprizes(coin, state);
}
