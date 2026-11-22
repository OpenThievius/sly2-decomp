// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "rsmg.h"
extern "C" {
void TriggerRsmgEntry(void *psw, RSMG *prsmg, s32 context, s32 flags, void *subscriber, void **out);
void TriggerRsmg(void *psw, s32 crsmg, RSMG *arsmg, s32 context, s32 flags) {
    if (crsmg > 0) {
        RSMG *prsmg = arsmg;
        s32 crsmgLeft = crsmg;
        do {
            TriggerRsmgEntry(psw, prsmg, context, flags, 0, 0);
            crsmgLeft -= 1;
            prsmg += 1;
        } while (crsmgLeft != 0);
    }
}
}
