#include "cref.h"
struct SLOT { char pad[0x5464]; };
struct SAVE {
    char pad0[0x24]; SLOT aslot[3];
    char pad2[0xFD50 - 0x24 - 3 * 0x5464];
    SLOT *pslotCur;
};
struct ENTRY { char pad[0x14]; int slot; int pad18; };
struct PAUSEMENU { char pad[0x24]; int count; };
struct MENU { char pad[0x44]; int phase; };
extern "C" {
#include "sw.h"
extern SW B_003DD490;
extern MENU B_002E6550;
extern SAVE B_002E65E0;
extern PAUSEMENU B_003D9ED0;
extern ENTRY B_003D9EDC[];
void func_001ACC38(MENU *, int);
CRef RefGetGameSaveValue(void *, void *);
int func_001B0078(PAUSEMENU *);
void func_001AD538(void)
{
    float values[3];
    func_001ACC38(&B_002E6550, 1);
    if (B_003D9ED0.count > 0) {
        ENTRY *entry = &B_003D9EDC[B_003D9ED0.count];
        for (int index = 0; index < 3; index++) {
            float value = RefGetGameSaveValue(B_003DD490.psavepathDt, &B_002E65E0.aslot[index]).m_tag.m_g;
            values[index] = value;
        }
        switch (func_001B0078(&B_003D9ED0)) {
        case 30:
            for (int index = 0; index < 3; index++) {
                if (values[index] == 0.0f) {
                    entry->slot = index;
                    break;
                }
            }
            break;
        case 31:
            for (int index = 0; index < 3; index++) {
                if (values[index] != 0.0f) {
                    entry->slot = index;
                    break;
                }
            }
            break;
        case 25:
            if (B_002E65E0.pslotCur != 0)
                entry->slot = B_002E65E0.pslotCur - B_002E65E0.aslot;
            break;
        }
    }
}
}
