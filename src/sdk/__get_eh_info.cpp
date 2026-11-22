/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
extern "C" {
extern void *(*D_002C60BC)();
void *__get_eh_info(void) {
    return (char *)D_002C60BC() + 8;
}
}
