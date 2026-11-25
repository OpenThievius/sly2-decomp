// SPDX-License-Identifier: GPL-3.0-or-later
#include "dprize.h"

extern "C" void HandleLoMessage(DPRIZE *, int msgid, void *pv);

// HandleDprizeMessage (SO slot 5 override): message 10 is an SMA event; the prize's own animation reaching event 0x186 tells the
// expire sink {1, prize} and moves to state 2
void func_001C5098(DPRIZE *pdprize, int msgid, SMAMSG *pmsg)
{
    HandleLoMessage(pdprize, msgid, pmsg);
    if (msgid == 10) {
        if (pmsg->psma == pdprize->psma) {
            if (pmsg->event == 0x186) {
                MSGSINK *psink = (MSGSINK *)pdprize->aoidploB[2].plo;
                if (psink) {
                    int amsg[16];
                    amsg[0] = 1;
                    amsg[1] = (sptr)pdprize;
                    psink->Notify(amsg);
                }
                pdprize->SetDprizes(2);
            }
        }
    }
}
