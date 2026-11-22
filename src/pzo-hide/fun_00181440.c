/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "pzo_hide.h"

void func_0017F138(struct GRAB *);
void func_0017F408(struct GRAB *, s32, struct ANIMENTRY *);

void func_00181440(struct GRAB *grab) {
    func_0017F138(grab);
    func_0017F408(grab, 3, grab->aentry);
}
