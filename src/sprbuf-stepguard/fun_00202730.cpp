// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "recon.h"
extern "C" char B_003DD490;
extern "C" const char *PchzStringFromId(void *, int);
extern "C" const char *func_00202730(BINOCRECON *precon)
{
    if (precon->sidA == -1) return 0;
    return PchzStringFromId(&B_003DD490, precon->sidA);
}
