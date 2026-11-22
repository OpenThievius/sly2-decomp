/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "jt.h"

extern "C" {
void func_00193DE8(void *pvAttach);
void func_001991A0(void *pvJmp);
void func_0019E950(void *pvPipe);
void func_001F4FA8(JT *pjt);

void func_00140D00(JT *pjt) {
    func_001F4FA8(pjt);
    if (pjt->jmpState != -1) {
        func_001991A0(pjt->PvJmp());
    }
    if (pjt->field_0x4CC != -1) {
        func_00193DE8(pjt->PvAttach());
    }
    if (pjt->field_0xF54 != -1) {
        func_0019E950(pjt->PvPipe());
    }
}
}
