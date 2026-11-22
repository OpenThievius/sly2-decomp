/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "hbsk.h"

void InitSo(struct HBSK *phbsk);                               /* extern */
void SetAloInteract(struct HBSK *phbsk, s32 grfInteract, s32 grfMask); /* extern */
void bevy_player_p6_182c70(struct MEMBER *pmember);            /* extern */

void InitHbsk__FP4HBSK(struct HBSK *phbsk) {
    InitSo(phbsk);
    bevy_player_p6_182c70(&phbsk->member);
    phbsk->hbsks = 0;
    phbsk->member.field_0x8 = 300.0f;
    phbsk->fLocked = 1;
    SetAloInteract(phbsk, 0x03FFFFFF, 8);
    SetAloInteract(phbsk, 0x03188001, 0);
}
