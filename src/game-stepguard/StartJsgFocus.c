/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jsg.h"

struct SW;
struct PO;
struct PO *PpoSwFocusBase(struct SW *);
void StartJsg(struct JSG *, struct PO *);
extern struct SW B_003DD490;

void StartJsgFocus(struct JSG *jsg) {
    StartJsg(jsg, PpoSwFocusBase(&B_003DD490));
}
