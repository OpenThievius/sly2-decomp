/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct SW;
struct SO;
void *PoxaAllocSw(struct SW *, struct SO *);
extern struct SW B_003DD490;

void PoxaAllocSo(struct SO *pso) {
    PoxaAllocSw(&B_003DD490, pso);
}
