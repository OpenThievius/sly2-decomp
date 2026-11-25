#include "loot.h"
/* UpdatePickLoot's view of the selected LOOTDEF: the flag that makes the loot drop from the thief once the clock passes a time (one reader) */
struct LOOTDEFTIMED { u8 unknown_0x0[0xC]; s32 timed; };
extern "C" void UpdateSo(LOOT *, float);
extern "C" void ReturnLootToGuard(LOOT *, int);
extern "C" void DropJtLoot(int);
extern float g_2dded0;
extern float B_003E1BFC;
void UpdatePickLoot(LOOT *loot, float dt)
{
    UpdateSo(loot, dt);
    int state = loot->state;
    if (state != 4) {
        if (state == 5) {
            if (5.0f <= g_2dded0 - loot->tState)
                ReturnLootToGuard(loot, 0);
        }
    } else {
        if (((LOOTDEFTIMED *)loot->plootdefSel)->timed != 0 && g_2dded0 >= B_003E1BFC)
            DropJtLoot(loot->idThief);
    }
}
