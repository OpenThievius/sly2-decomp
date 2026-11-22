// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

struct SAVEVARREC { short symid; signed char savek; unsigned char cElement; unsigned short ib; unsigned short irecChild; unsigned short irecNext; };
struct SAVEVARS;
struct SAVEPATH;
struct SAVEVARLOC { SAVEVARREC *prec; int iElement; };

extern "C" {
extern s32 D_002C2D90[];
int FFindSaveVar(SAVEVARS *psavevars, SAVEPATH *ppath, SAVEVARLOC *psavevarloc);
char *PvFindSaveVar(SAVEVARS *psavevars, SAVEPATH *ppath, char *base) {
    SAVEVARLOC savevarloc;
    FFindSaveVar(psavevars, ppath, &savevarloc);
    return base + (savevarloc.prec->ib + savevarloc.iElement * D_002C2D90[savevarloc.prec->savek]);
}
}
