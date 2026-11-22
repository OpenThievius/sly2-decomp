/* SPDX-License-Identifier: GPL-3.0-or-later */
struct SLOTHEAP;

void FreeSlotheapPv(struct SLOTHEAP *, void *);
extern struct SLOTHEAP B_003E123C;

void FreeAct(void *pact) {
    FreeSlotheapPv(&B_003E123C, pact);
}
