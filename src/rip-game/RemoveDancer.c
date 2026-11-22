/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct DANCER_1520C8;

void RemoveSoLoHierarchy();
void PlayDancerAnim(struct DANCER_1520C8 *, void *, s32);

void RemoveDancer(struct DANCER_1520C8 *dancer) {
    RemoveSoLoHierarchy();
    PlayDancerAnim(dancer, 0, 0);
}
