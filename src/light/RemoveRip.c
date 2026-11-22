/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rip.h"

void ReleaseRip(struct RIP *rip);
void RemoveDlEntry(struct DL *pdl, void *pv);

void RemoveRip(struct RIP *rip) {
    RemoveDlEntry(&rip->pripg->rips, rip);
    ReleaseRip(rip);
}
