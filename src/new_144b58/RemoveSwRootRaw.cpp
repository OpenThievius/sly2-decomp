// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"

extern "C" void RemoveDlEntry(DL *pdl, void *pv);

extern "C" void RemoveSwRootRaw(SW *psw, void *proot)
{
    RemoveDlEntry(&psw->dlRoot, proot);
}
