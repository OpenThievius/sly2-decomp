/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "keypad.h"
#include "soproperty.h"

s32 FVaultOpen(void);
void PostSoLoad(struct KEYPAD *pkeypad);
void SetSoProperties(struct KEYPAD *pkeypad, s32 cprop, const SOPROPERTY *aprop);
void func_001C8730(struct KEYPAD *pkeypad, s32 state);
struct XF *func_001F4C58(struct KEYPAD *pkeypad, s32 oid, s32 kind);
extern SOPROPERTY D_002C0EC8[24];

void func_001C82F0(struct KEYPAD *pkeypad) {
    PostSoLoad(pkeypad);
    SetSoProperties(pkeypad, 0x18, D_002C0EC8);
    pkeypad->pxf = func_001F4C58(pkeypad, 0x645, 1);
    func_001C8730(pkeypad, (FVaultOpen() == 0) ? 0 : 5);
}
