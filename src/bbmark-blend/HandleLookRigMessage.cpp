// SPDX-License-Identifier: GPL-3.0-or-later
#include "lookrig.h"
extern "C" {
void func_00131B10(s32 key, void *pjt, void *powner);

void HandleLookRigMessage(LOOKRIG *plookrig, s32 msgid, s32 *pv) {
    s32 sender;
    s32 messageKind;
    JT *pjt;

    if ((msgid == 9) && (sender = pv[0], (sender == (s32)plookrig->phandle))) {
        messageKind = pv[2];
        switch (messageKind) {                      /* irregular */
        case 0x16E:
            pjt = plookrig->pjt;
            func_00131B10(sender, pjt, pjt->field_0x10B8);
            plookrig->fSnap = 1;
            return;
        case 0x242:
            plookrig->field_0xC = 1;
            break;
        }
    }
}

}
