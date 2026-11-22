// SPDX-License-Identifier: GPL-3.0-or-later
#include "bentley.h"
#include "sly2.h"
extern "C" void *PasegAttachBase(void *, int *);
extern "C" void *bevy_player_p7_damage_1a23f8(void *, int *);
extern "C" void *func_0019C870(void *, int *);
extern "C" void func_00203D00(BENTLEY *, void *, int);
void SetBentleyAnimBase(BENTLEY *pbentley)
{
    int flag = 0;
    void *pasegBase;
    int state = pbentley->state;
    switch (state) {
    case 3: pasegBase = PasegAttachBase(pbentley->PvAttach(), &flag); break;
    case 4: pasegBase = bevy_player_p7_damage_1a23f8(pbentley->PvZap(), &flag); break;
    case 2: pasegBase = func_0019C870(pbentley->PvJmp(), &flag); break;
    default: pasegBase = 0;
    }
    if (!pasegBase) pasegBase = pbentley->pasegDefault;
    func_00203D00(pbentley, pasegBase, flag);
}
