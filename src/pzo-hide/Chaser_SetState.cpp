// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"
extern "C" void func_0017F4C0(SOHIT *, ANIMENTRY *);

void Chaser_SetState(CHASER *chaser, int state)
{
    int stateOld = chaser->state;
    if (stateOld == state)
        return;
    if (stateOld == -1)
        chaser->hp = chaser->hpMax;
    chaser->state = state;
    chaser->tState = g_2dded0.t;
    if (state != 3) {
        if (state < 4) {
            if (state >= 0) {
                s32 *pvec = chaser->field_0x210;
                pvec[2] = 0;
                pvec[1] = 0;
                pvec[0] = 0;
            }
        } else if (state == 4) {
            s32 *pvec = chaser->field_0x210;
            pvec[2] = 0;
            pvec[1] = 0;
            pvec[0] = 0;
        }
    }
    ANIMENTRY *pentry = (state == -1) ? 0 : &chaser->aentry[state];
    func_0017F4C0(chaser, pentry);
}
