// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
/* a world string, 8 bytes: its id and the text (declared by its users, as LoadSwStringsFromBrx does) */
struct SWSTRING { int id; char *pch; };
extern "C" const char RO_002A4BE0[];
extern "C" char *PchzStringFromId(SW *psw, int id)
{
    if (id == -1)
        return (char *)RO_002A4BE0;
    for (int i = 0; i < psw->field_0x4640; i++) {
        if (psw->astring[i].id == id)
            return psw->astring[i].pch;
    }
    return (char *)RO_002A4BE0;
}
