/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

struct SW;
extern struct SW B_003DD490;

void func_001A6178(struct LIGHT *light);
void AddLightToSw(struct SW *psw, struct LIGHT *light);

void OnLightAdd(struct LIGHT *light) {
    func_001A6178(light);
    AddLightToSw(&B_003DD490, light);
}
