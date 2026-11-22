/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "rogwindow.h"

struct VIFS;
void func_0016E1A8(struct VIFS *pvifs, s32 argument1, s32 argument2);
void func_001BE6F0(struct ROGWINDOW *pwindow, struct VIFS *pvifs);
extern struct ROGWINDOW B_003E1A78[];

void func_001BE990(struct VIFS *pvifs, s32 argument1, s32 argument2) {
    func_001BE6F0(B_003E1A78, pvifs);
    func_0016E1A8(pvifs, argument1, argument2);
}
