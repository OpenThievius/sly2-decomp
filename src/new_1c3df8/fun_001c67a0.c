/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct GAME; /* the game-state object at 0x2DEB30: its coin count is read and written through these two functions */
s32 GetGameCoins(struct GAME *pgame);            /* extern */
void SetGameCoins(struct GAME *pgame, s32 ccoin); /* extern */
extern struct GAME B_002DEB30;

/* CollectDprizeCoinDirect: SetDprizeCoinDprizes calls it with the prize and 0 when no RIP is free; neither is read */
void func_001C67A0(void *pdprize, s32 unused) {
    SetGameCoins(&B_002DEB30, GetGameCoins(&B_002DEB30) + 1);
}
