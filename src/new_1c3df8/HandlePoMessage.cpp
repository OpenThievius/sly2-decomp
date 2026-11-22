// SPDX-License-Identifier: GPL-3.0-or-later
#include "po.h"

struct AMB;
extern "C" {
void HandleLoMessage(PO *ppo, int msgid, void *pv);
void StopAmb(AMB *pamb, float uFade);
void VirtualRefPtr_Assign(void *pref, void *pvalue);

void HandlePoMessage(PO *ppo, int msgid, void *pv) {
    HandleLoMessage(ppo, msgid, pv);
    if (msgid == 5) {
        if (&ppo->pamb != 0) {
            AMB *pamb = ppo->pamb;
            if (pamb != 0) {
                StopAmb(pamb, 0);
                VirtualRefPtr_Assign(&ppo->pamb, 0);
            }
        }
    }
}
}
