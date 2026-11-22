// SPDX-License-Identifier: GPL-3.0-or-later
#include "pausemenu.h"
extern "C" {
s32 func_001B0078(PAUSEMENU *pmenu);

s32 func_001B0108(PAUSEMENU *pmenu) {
    s32 kind;
    s32 result;

    kind = func_001B0078(pmenu);
    if (kind != 0x19) {
        if (kind >= 0x19) {
            if (kind < 0x20) {
                if (kind >= 0x1E) {
                    goto accept;
                }
                { result = 0; goto done; }
            }
            { result = 0; goto done; }
        }
        return 0;
    }
accept:
    return 1;
done:
    return result;
}

}
