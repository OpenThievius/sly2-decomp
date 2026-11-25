// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
/* the goal func_00205458 finds (kind 0xA9): only this function reads its word at 0x4C */
struct GOALVIEW_206EB0 { u8 unknown_0x0[0x4C]; s32 field_0x4C; };
extern "C" {
int FIsBasicDerivedFrom(STEPGUARD *, int);
int FIsGuardInSgs(STEPGUARD *, int);
int FIsGuardSpecialClass(STEPGUARD *);
GOALVIEW_206EB0 *func_00205458(STEPGUARD *, int);
int FCanSetGuardMode(STEPGUARD *guard, int mode)
{
    int result;
    if (mode == -1) return 1;
    if (FIsGuardInSgs(guard, 7) != 0) return 0;
    GOALVIEW_206EB0 *entry = func_00205458(guard, 0xA9);
    if (entry != 0) {
        if (entry->field_0x4C != 0) return 0;
    }
    switch (mode - 8) {
    case 0:
    case 5:
    case 6:
        return 1;
    case 13:
        result = 0;
        if (FIsBasicDerivedFrom(guard, 0x3E) != 0) goto done;
        if (FIsBasicDerivedFrom(guard, 0x42) != 0) goto done;
        result = FIsBasicDerivedFrom(guard, 0x43) == 0;
        goto done;
    case 26:
    case 29:
        return FIsGuardSpecialClass(guard) == 0;
    case 3:
        result = 0;
        if (FIsBasicDerivedFrom(guard, 0x3B) != 0) goto done;
        if (FIsBasicDerivedFrom(guard, 0x3D) != 0) goto done;
        if (FIsBasicDerivedFrom(guard, 0x40) != 0) goto done;
        if (FIsBasicDerivedFrom(guard, 0x3E) != 0) goto done;
        if (FIsBasicDerivedFrom(guard, 0x41) != 0) goto done;
        if (FIsBasicDerivedFrom(guard, 0x3F) != 0) goto done;
        if (FIsBasicDerivedFrom(guard, 0x3C) != 0) goto done;
        if (FIsBasicDerivedFrom(guard, 0x42) != 0) goto done;
        result = FIsBasicDerivedFrom(guard, 0x43) == 0;
    done:
        return result;
    default:
        return 0;
    }
}
}
