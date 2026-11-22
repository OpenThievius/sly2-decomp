// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "cref.h"
// The message an owner's slot 51 receives (0x40 bytes; SetCluebottleState 0x1C7EE8 sends the same one, FAbsorbSlotSoWkr
// 0x1B0F88 fills vectors at 0x10 and 0x20 of it).
struct NOTICE { int a; void *b; u8 unknown_0x8[0x38]; };
struct VTB { char pad[0x198]; short delta; short index; void (*fn)(void *, NOTICE *); };
struct OBJ { char pad[0xC]; VTB *vt; };
struct VTC { char pad[0x18]; short delta; short index; void (*fn)(void *, int, int, int, int, int); };
struct LOOTDEF { int pad; int lootkc; };
struct COIN { char pad0[0xC]; VTC *vt; char pad1[0x150 - 0x10]; int state; char pad2[0x210 - 0x154]; OBJ *owner; char pad3[0x230 - 0x214]; float waitMin; float waitMax; float wait; char pad4[0x244 - 0x23C]; LOOTDEF *lootdef; };
extern "C" {
float GRandInRange(float, float);
CRef func_001D8A38(const char *first, ...);
CRef func_001D8B20(const CRef &value, const char *first, ...);
int sprintf(char *, const char *, ...);
void SetDprizeDprizes(COIN *, int);
extern const char RO_002A7768[];
extern const char RO_002A7770[];
extern const char RO_002A7778[];
}

void SetCoinState(COIN *coin, int state)
{
    if (coin->state == state) return;
    switch (state) {
    case 0:
        coin->wait = GRandInRange(coin->waitMin, coin->waitMax);
        break;
    case 1: {
        CRef ref;
        char name[0x10];
        ref.m_tagk = TAGK_Nil;
        sprintf(name, RO_002A7768, coin->lootdef->lootkc);
        ref = func_001D8A38(RO_002A7770, RO_002A7778, name, 0);
        func_001D8B20(CRef(ref.m_tag.m_n + 1, TAGK_S32), RO_002A7770, RO_002A7778, name, 0);
        OBJ *owner = coin->owner;
        if (owner) {
            NOTICE notice;
            notice.a = state;
            notice.b = coin;
            VTB *vt = owner->vt;
            vt->fn((char *)owner + vt->delta, &notice);
        }
        state = 2;
        coin->vt->fn((char *)coin + coin->vt->delta, 5, 0, 0, 0, 0);
        break;
    }
    }
    SetDprizeDprizes(coin, state);
}
