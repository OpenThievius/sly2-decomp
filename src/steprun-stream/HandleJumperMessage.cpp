// SPDX-License-Identifier: GPL-3.0-or-later
#include "guard.h"

// a message to the jumper: id 9 carries the event code at 0x8 (0x22 is the one that restarts the jump)
struct JUMPERMESSAGE {
    u8 unknown_0x0[0x8];
    s32 event;
};

extern "C" {
void HandleLoMessage(JUMPER *, int, JUMPERMESSAGE *);
void SetJumperState(JUMPER *, int);

void HandleJumperMessage(JUMPER *pjumper, int msgid, JUMPERMESSAGE *pmessage) {
    if ((msgid == 9) && (pmessage->event == 0x22)) {
        SetJumperState(pjumper, 1);
    }
    HandleLoMessage(pjumper, msgid, pmessage);
}

}
