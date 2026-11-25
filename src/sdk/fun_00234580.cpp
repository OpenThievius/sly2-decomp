/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"
#include "libcstate.h"
extern "C" {
s64 func_00234350(int *, const char *, char **, int);
extern LIBCSTATE *D_002C49D4;
void func_00234580(const char *text, char **end, int base) {
    func_00234350(&D_002C49D4->errorNumber, text, end, base);
}
}
