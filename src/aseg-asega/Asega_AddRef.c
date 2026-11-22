/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "asega.h"

void Asega_AddRef(struct ASEGA *pasega) {
    pasega->cref = pasega->cref + 1;
}
