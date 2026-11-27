// SPDX-License-Identifier: GPL-3.0-or-later
#include "button.h"
#include "sly.h"
#include "oxa.h"
#include "xp.h"
#include "sw.h"
#include "sly2.h"

struct UL { u64 v; } __attribute__((packed));
extern "C" const UL RO_002A4E80;
extern "C" SW B_003DD490;
extern "C" {
void UpdateSo(void);
void SetButtonButtons(BUTTON *, unsigned);
int FCheckButtonObject(BUTTON *, SO *);
void QueueSwCallbackOnce(SW *, BUTTON *, u64, int);
}
extern SLY *g_2e1e40; /* the player */
extern float g_2dded0;
extern "C" void UpdateButton(BUTTON *button)
{
    UpdateSo();
    switch (button->btn.buttons) {
    case 2:
        if (g_2e1e40 != 0 && g_2e1e40->jts == 3 && (s32)g_2e1e40->pjtcsinfo == button->id)
            button->btn.tButtons = g_2dded0;
        {
            float time = button->btn.dtRepush;
            if (time >= 0.0f && time < g_2dded0 - button->btn.tButtons)
                SetButtonButtons(button, 4);
        }
        break;
    case 3:
    default:
        break;
    case 4: {
        int buttons = -1;
        switch (button->btnt) {
        case 0: case 2: case 3: buttons = 1; break;
        case 1: buttons = 0; break;
        }
        if (buttons != -1) SetButtonButtons(button, buttons);
        break;
    }
    case 0:
    case 1: {
        unsigned buttons = button->btn.buttons;
        switch (button->btnt) {
        case 1:
        case 2:
            break;
        case 3:
            buttons = 0;
            if (g_2e1e40 != 0) {
                if (g_2e1e40->jts == 3)
                    buttons = (s32)g_2e1e40->pjtcsinfo == button->id;
            }
            break;
        case 0:
            OX *pox = button->poxa->first;
            buttons = 0;
            for (; pox != 0; pox = pox->next) {
                for (XP *pxp = pox->pxp; pxp != 0; pxp = pxp->pxpNext) {
                    if (pxp->kind == 10) continue;
                    int side = button->poxa->owner != pxp->axpd[0].psoRoot;
                    SO *psoOther = pxp->axpd[1 - side].psoRoot;
                    if (pxp->axpd[side].pso == button && FCheckButtonObject(button, psoOther)) {
                        button->ptarget = psoOther;
                        QueueSwCallbackOnce(&B_003DD490, button, RO_002A4E80.v, 0);
                        buttons = button->btn.buttons;
                        goto done;
                    }
                }
            }
            break;
        }
    done:
        SetButtonButtons(button, buttons);
        break;
    }
    }
}
