// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
extern "C" int FIsBasicDerivedFrom(void *, int);
extern "C" int FAbsorbSoWkr(void *, void *);
extern "C" void GoalStack_HandleMessage(void *, int, void *);
struct WKR { void *src; int f4; int f8; int kind; };
int FAbsorbGuardWkr(STEPGUARD *g, WKR *w)
{
    if (g->FLethalHit()) goto post;
    if (g->FInvulnerable(w->kind)) return 1;
    if (w->src && FIsBasicDerivedFrom(w->src, 0x4F) && *(int *)(*(char **)((char *)w->src + 0x200) + 0x14) == g->proot) return 1;
    if (!FAbsorbSoWkr(g, w)) return 0;
post:
    GoalStack_HandleMessage((char *)g + 0x26C, 0xC, w);
    return 1;
}
