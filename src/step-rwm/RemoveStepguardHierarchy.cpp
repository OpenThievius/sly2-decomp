// SPDX-License-Identifier: GPL-3.0-or-later
#include "stepguard.h"
#include "goals.h"
#include "dl.h"
#include "clock.h"
extern "C" {
void RemoveDlEntry(DL *, void *);
void func_001F3E00(void *);
extern DL B_003E1444;

void RemoveStepguardHierarchy(STEPGUARD *pguard) {
    func_001F3E00(pguard);
    RemoveDlEntry(&B_003E1444, pguard);
    pguard->field_0xFF8 = g_2dded0.t;
}

}
