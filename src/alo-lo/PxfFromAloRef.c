/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "alo.h"

void PxfFromRef(int, struct SO *, struct ALO *);

void PxfFromAloRef(struct ALO *palo, int id) {
    PxfFromRef(id, palo->psoParent, palo);
}
