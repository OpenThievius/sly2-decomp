/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void func_0017F090(struct GRAB *);
void func_0017F3E0(struct GRAB *, s32, struct ANIMENTRY *);

void func_00181408(struct GRAB *grab) {
    func_0017F090(grab);
    func_0017F3E0(grab, 3, grab->aentry);
}
