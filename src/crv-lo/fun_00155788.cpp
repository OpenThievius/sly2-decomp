// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
struct VT { char pad[0x40]; short delta; short index; void (*fn)(void *); };
struct GO { char pad[0x0C]; VT *vptr; char pad1[0x30 - 0x10]; void *a30; char p34[4]; void *a38; char p3c[4]; int a40; char pad2[0x4C - 0x44]; void *a4C; };
#include "stepguard.h"
struct GUARD : STEPGUARD { u8 unknown_0x1010[0x8]; int tickPick; };
struct POST { char pad[0x20]; int used; };
struct PG { char pad[0x10]; GUARD *guard; char pad2[0x18 - 0x14]; char child[0x18]; int state; float t; void *target; POST *post; };
extern "C" void Goal_Pop(void *);
extern "C" GO *func_00205438(GUARD *, int);
extern float g_2dded0;
struct CK { float t; };
extern "C" void func_00155788(PG *pg, int state)
{
    if (state == pg->state) return;
    if (pg->state == 0) pg->post->used = 1;
    Goal_Pop(pg->child);
    pg->state = state;
    pg->t = ((CK*)&g_2dded0)->t;
    switch (state) {
    case 0: {
        GO *go = func_00205438(pg->guard, 0xB5);
        go->a38 = pg->post;
        go->a4C = pg->target;
        VT *vt = go->vptr;
        vt->fn((char *)go + vt->delta);
        pg->guard->tickPick = pg->guard->field_0x33C;
        break; }
    case 1: {
        GO *go = func_00205438(pg->guard, 0xA5);
        void *tg = pg->target;
        go->a40 = state;
        go->a30 = tg;
        VT *vt = go->vptr;
        vt->fn((char *)go + vt->delta);
        break; }
    }
}
