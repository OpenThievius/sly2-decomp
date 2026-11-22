// SPDX-License-Identifier: GPL-3.0-or-later
#include "streamamb.h"
extern "C" {
STREAMAMB *InitStreamAmb(STREAMAMB *pamb, s32 record, s32 start);
void *PvAllocStreamAmb(s32 cb);

STREAMAMB *NewStreamAmb(s32 record, s32 start) {
    STREAMAMB *result;
    if (record != 0) {
        { result = InitStreamAmb((STREAMAMB *)PvAllocStreamAmb(0x3C0), record, start); goto done; }
    }
    { result = 0; goto done; }
done:
    return result;
}

}
