// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" float g_2dded0;
extern "C" const float D_002C3D40;
extern "C" const float D_002C3D44;
extern "C" const float D_002C3D48;
void SetGuardMode(STEPGUARD *, int);

void UpdateGuardModeTimeout(STEPGUARD *guard)
{
    switch (guard->mode) {
    case 8:
    case 13:
        if (D_002C3D40 < g_2dded0 - guard->tMode) {
            SetGuardMode(guard, -1);
        }
        break;
    case 34:
    case 37:
        if (D_002C3D44 < g_2dded0 - guard->tMode) {
            SetGuardMode(guard, -1);
        }
        break;
    case 21:
        if (D_002C3D48 < g_2dded0 - guard->tMode) {
            SetGuardMode(guard, -1);
        }
        break;
    }
}
