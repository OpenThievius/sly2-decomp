// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly.h"
struct JOY { char pad[0x30]; unsigned grfbtn; };
extern "C" {
int FButtonPressedWithin(JOY *pjoy, int grfbtn, float dt);
void SetJmpState(void *pjmp, int jmps, int arg1, int arg2);
void SetJtState(JT *pjt, int jts, int jtbs);
void SetJtJtcs(SLY *psly, int jtcs);
int ChooseJtCaneSwing(SLY *psly);
int ChooseJtCaneAlternateSwing(SLY *psly);
}
extern "C" void UpdateJtCaneInput(SLY *psly)
{
    int fSwing;
    if (psly->jtcs < 0x16) {
        if (psly->jtcs >= 0xC && !(psly->pjoy->grfbtn & 0x80)) {
            psly->field_0x18EC = 0;
        }
    }
    fSwing = 0;
    switch (psly->jts) {
    case 3:
    case 21:
    case 22:
        if (FButtonPressedWithin(psly->pjoy, 0x80, 0.0f)) {
            SetJmpState(psly->PvJmp(), 0, 0, 0);
        }
        break;
    case 7:
        if (psly->attachKind < 5) {
            fSwing = psly->attachKind >= 3;
        }
        break;
    case 5: {
        int jtbs = psly->field_0x18D0;
        if (jtbs >= 6) {
            if (jtbs >= 8) {
                if (jtbs >= 10) {
                    goto swing;
                }
                return;
            } else {
                if (!(psly->pjoy->grfbtn & 0x80)) {
                    if (*(s32 *)psly->unknown_0x18E8) {
                        SetJtState(psly, 5, 8);
                    } else {
                        SetJtState(psly, 5, 4);
                    }
                }
                break;
            }
        }
    }
    case 0:
    case 1:
    case 10:
    case 12:
    swing:
        fSwing = 1;
        break;
    }
    if (!fSwing) {
        return;
    }
    switch (psly->jtcs) {
    case -1:
        break;
    case 12: case 13: case 14: case 15: case 16: case 17:
    case 18: case 19: case 20: case 21: case 22: case 23:
        if (!psly->field_0x18E4) {
            return;
        }
        break;
    default:
        return;
    }
    if (FButtonPressedWithin(psly->pjoy, 0x10, 0.35f)) {
        SetJtJtcs(psly, -1);
        SetJtJtcs(psly, ChooseJtCaneAlternateSwing(psly));
    } else if (FButtonPressedWithin(psly->pjoy, 0x80, 0.35f)) {
        SetJtJtcs(psly, -1);
        SetJtJtcs(psly, ChooseJtCaneSwing(psly));
    }
}
