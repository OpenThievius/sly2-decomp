/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

void BuildBlipAqwGifs__FiPP2QW(s32 ialpha, QW **paqw);
extern QW *B_002DD5C0;
extern QW *B_002DD600;

void StartupBlips__Fv(void) {
    BuildBlipAqwGifs__FiPP2QW(1, &B_002DD5C0);
    BuildBlipAqwGifs__FiPP2QW(2, &B_002DD600);
}
