// SPDX-License-Identifier: GPL-3.0-or-later
#include "keypad.h"
extern "C" {
int FIsJsgActive(int);
void SetVaultOpen(int);
void UpdateSo(KEYPAD *);
void func_001C84D8(KEYPAD *);
void func_001C8730(KEYPAD *, int);
void func_001C8350(KEYPAD *keypad)
{
    UpdateSo(keypad);
    int state;
    do {
        state = keypad->state;
        switch (state) {
        case 1:
            if (keypad->jsg == 0 || FIsJsgActive(keypad->jsg) == 0)
                func_001C8730(keypad, 2);
            break;
        case 2:
            if (keypad->jsg == 0 || FIsJsgActive(keypad->jsg) == 0) {
                if (keypad->target == keypad->field_0x1F0)
                    func_001C8730(keypad, 3);
                else
                    func_001C8730(keypad, 4);
            } else {
                func_001C84D8(keypad);
            }
            break;
        case 4:
            if (keypad->jsg == 0 || FIsJsgActive(keypad->jsg) == 0)
                func_001C8730(keypad, 0);
            break;
        case 3:
            if (keypad->jsg == 0 || FIsJsgActive(keypad->jsg) == 0) {
                SetVaultOpen(1);
                func_001C8730(keypad, 5);
            }
            break;
        }
    } while (keypad->state != state);
}
}
