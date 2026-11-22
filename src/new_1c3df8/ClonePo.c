/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* a PO's own fields up to 0x168 are not recovered here (po.h is C++ only): ClonePo (slot 41) stores the object into 0x168 after the
   SO clone (PO::ppoSelf) */
struct POVIEW {
    u8 unknown_0x0[0x168];
    /* 0x168 */ struct POVIEW *ppoSelf;
};

void CSo_Clone(struct POVIEW *ppo, struct POVIEW *ppoSource); /* extern */

void ClonePo(struct POVIEW *ppo, struct POVIEW *ppoSource) {
    CSo_Clone(ppo, ppoSource);
    ppo->ppoSelf = ppo;
}
