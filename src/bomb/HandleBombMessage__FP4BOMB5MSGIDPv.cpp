/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "so.h"

enum MSGID { MSGID_PRIME = 4 };

/* A bomb: an SO with its primed flag first. */
struct BOMB : SO {
    /* 0x150 */ s32 fPrimed; /* HandleBombMessage: PrimeBomb only while 0 */
};

/* Message 4's data: the bomb it is about at word 4. */
struct BOMBMSG {
    u8 unknown_0x0[0x4];
    /* 0x4 */ BOMB *pbomb; /* HandleBombMessage */
};

extern "C" void HandleLoMessage(SO *, int, void *);
float PrimeBomb(BOMB *pbomb, float t);

void HandleBombMessage(BOMB *pbomb, MSGID msgid, void *pv)
{
    HandleLoMessage(pbomb, msgid, pv);
    if (msgid == MSGID_PRIME) {
        BOMB *pbombMsg = ((BOMBMSG *)pv)->pbomb;
        if (pbombMsg == pbomb && pbombMsg->fPrimed == 0) {
            PrimeBomb(pbombMsg, 0.0f);
        }
    }
}
