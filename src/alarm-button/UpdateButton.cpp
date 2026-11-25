// SPDX-License-Identifier: GPL-3.0-or-later
#include "button.h"
#include "sw.h"
#include "sly2.h"

struct UL { u64 v; } __attribute__((packed));
extern "C" const UL RO_002A4E80;
extern "C" SW B_003DD490;
/* one half of a contact (0x40 bytes, two per contact): the object and the object it touches */
/* the object g_2e1e40 points at (the player: SLY::jts is its 0x18C8, SLY::pjtcsinfo its 0x18C4, which UpdateButton compares with a button id): one reader, so a view */
/* what g_2e1e40 points at, the player (sly.h: SLY::pjtcsinfo is its 0x18C4, SLY::jts its 0x18C8); one reader, so a view */
struct PLAYERVIEW { u8 unknown_0x0[0x18C4]; s32 id; s32 jts; };
struct XPSIDE { u8 unknown_0x0[0x8]; SO *pso; BUTTON *pbutton; u8 unknown_0x10[0x30]; };
struct XP { XPSIDE aside[2]; u8 unknown_0x80[0x1C]; s32 kind; u8 unknown_0xA0[0xC]; XP *pxpNext; };
struct XPGROUP { XP *pxpFirst; XPGROUP *pxpgroupNext; };
/* SO::poxa's block as UpdateButton reads it past OXA's declared part */
struct OXABOARD { u8 unknown_0x0[0x60]; SO *owner; XPGROUP *pxpgroupFirst; };
extern "C" {
void UpdateSo(void);
void SetButtonButtons(BUTTON *, unsigned);
int FCheckButtonObject(BUTTON *, SO *);
void QueueSwCallbackOnce(SW *, BUTTON *, u64, int);
}
extern PLAYERVIEW *g_2e1e40;
extern float g_2dded0;
extern "C" void UpdateButton(BUTTON *button)
{
    UpdateSo();
    switch (button->btn.buttons) {
    case 2:
        if (g_2e1e40 != 0 && g_2e1e40->jts == 3 && g_2e1e40->id == button->id)
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
                    buttons = g_2e1e40->id == button->id;
            }
            break;
        case 0:
            XPGROUP *pxpgroup = ((OXABOARD *)button->poxa)->pxpgroupFirst;
            buttons = 0;
            for (; pxpgroup != 0; pxpgroup = pxpgroup->pxpgroupNext) {
                for (XP *pxp = pxpgroup->pxpFirst; pxp != 0; pxp = pxp->pxpNext) {
                    if (pxp->kind == 10) continue;
                    int side = ((OXABOARD *)button->poxa)->owner != pxp->aside[0].pso;
                    SO *psoOther = pxp->aside[1 - side].pso;
                    if (((XPSIDE *)((char *)pxp + (side << 6)))->pbutton == button && FCheckButtonObject(button, psoOther)) {
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
