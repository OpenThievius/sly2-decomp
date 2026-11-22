// SPDX-License-Identifier: GPL-3.0-or-later
#include "pzo_hide.h"

extern "C" void Member_GetPosNearJt(MEMBER *member, void *joint, f32 *paramOut, void *position, f32 *heading)
{
    f32 param;
    member->GetParam(joint, &param);
    member->GetPosFromParam(param, joint, position, heading);
    if (paramOut != 0)
        *paramOut = param;
}
