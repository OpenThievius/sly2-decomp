// SPDX-License-Identifier: GPL-3.0-or-later
#include "mount.h"
#include "xf.h"
extern "C" {
void SetXfKind(SO *pso, XF *pxf, int kind);
void func_0017F138(MOUNT *pmount);
void func_0017F408(MOUNT *pmount, int centry, ANIMENTRY *aentry);
void func_0017F770(MOUNT *pmount);

void Mount_PostLoad(MOUNT *pmount) {
    func_0017F138(pmount);
    pmount->SetPlayable(0);
    SetXfKind(pmount, pmount->pxfLinear, 2);
    SetXfKind(pmount, pmount->pxfAngular, 2);
    func_0017F770(pmount);
    func_0017F408(pmount, 5, pmount->aentry);
}
}
