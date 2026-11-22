/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "light.h"

struct SW;
extern struct SW B_003DD490;

void RemoveAloHierarchy(struct LIGHT *light);
void RemoveLightFromSw(struct SW *psw, struct LIGHT *light);

void OnLightRemove(struct LIGHT *light) {
    RemoveAloHierarchy(light);
    RemoveLightFromSw(&B_003DD490, light);
}
