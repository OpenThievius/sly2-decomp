// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "sw.h"
#include "alloc.h"
struct ZPR { u8 unknown_0x0[0x630]; };
struct ACT;
extern "C" void *PvAllocSwImpl__Fi(ALLOCREQ *);
extern "C" void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
extern "C" void InitSl(void *, int);
extern "C" void InitZpr__FP3ZPR3ZPKP2LO(ZPR *, int, int);
extern "C" void func_001BE398(ZPRENTRY *, ZPR *);
extern "C" void bevy_camera_follow_activity(ACT *, int, void *);
extern "C" ACT B_002DEB30;
void AllocSwBuffers(SW *sw)
{
    ALLOCREQ req;
    ZPR zpr;
    OBR **slot = sw->aobr;
    for (int index = 2; index >= 0; index--) {
        req.cb = 0x4800;
        req.cbAlign = 0x10;
        *slot++ = (OBR *)PvAllocSwImpl__Fi(&req);
    }
    unsigned index = 0;
    ZPRENTRY *entry = sw->azprentry;
    req.cb = 0x8000;
    req.cbAlign = 0x10;
    sw->agrfentry = (GRFENTRY *)PvAllocSwClearImpl__Fi(&req);
    req.cb = 0x28;
    req.cbAlign = 0x10;
    SCOPE *pscope = (SCOPE *)PvAllocSwClearImpl__Fi(&req);
    sw->pscopeDefault = pscope;
    pscope->field_0x0 = -1;
    sw->pscopeDefault->field_0x8 = -1;
    InitSl(sw->pscopeDefault->sl, 0x14);
    InitZpr__FP3ZPR3ZPKP2LO(&zpr, 0x1400, 0x1800);
    for (; index < 2; index++) {
        func_001BE398(entry, &zpr);
        entry++;
    }
    if (sw->loadreq.grf & 0x20)
        sw->field_0x3E38 = 1;
    bevy_camera_follow_activity(&B_002DEB30, 2, 0);
}
