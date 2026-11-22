// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "dl.h"
extern "C" {
void AppendDlEntry(DL *, void *);
void func_001F3EA8(void *);
extern DL B_003E1444;
extern f32 RO_002A8868;

void AddStepguardHierarchy(STEPGUARD *pguard) {
    func_001F3EA8(pguard);
    AppendDlEntry(&B_003E1444, pguard);
    pguard->field_0xFF8 = RO_002A8868;
}

}
