/* SPDX-License-Identifier: GPL-3.0-or-later */
struct SLOTHEAP;

void *PvAllocSlotheapImpl(struct SLOTHEAP *);
extern struct SLOTHEAP B_003E123C;

void PvAllocAct(void) {
    PvAllocSlotheapImpl(&B_003E123C);
}
