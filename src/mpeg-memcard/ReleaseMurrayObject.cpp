// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "murray.h"
// The hand-written vtable calls of retail (a virtual call here does not reproduce the bytes): views of an LO's vtable pointer at 0xC.
struct VT18 { char pad[0x18]; short delta; short index; void (*fn)(char *, int, int, int, int, int); };
struct VT118 { char pad[0x118]; short delta; short index; void (*fn)(char *, QW); };
struct SLOT { short delta; short index; void (*fn)(char *, QW); };
struct VIEW18 { char pad0[0xC]; VT18 *vt; };
struct VIEW118 { char pad0[0xC]; VT118 *vt; };
extern const QW D_002C09E0;
extern const QW g_2a2dd0;
extern "C" {
void DetachMurrayObject(void *);
int FIsBasicDerivedFrom(void *, int);
void func_00209EE0(void *);
void func_001F7A68(void *, int);
void SetSmaGoal__FP3SMA3OID(void *, int);
QW bevy_camera_follow_track_heading_weight(void *, int, QW);
}

void ReleaseMurrayObject(MURRAY *pmurray)
{
    if (pmurray->state == 6) {
        if (pmurray->psmaPartner != 0)
            SetSmaGoal__FP3SMA3OID(pmurray->psmaPartner, 0x1CA);
        return;
    }
    LO *pobj = pmurray->ploCarried;
    if (pobj == 0) return;
    if (pmurray->state == 4 && pmurray->field_0x1450 == 0) {
        VIEW18 *pview = (VIEW18 *)pobj;
        pview->vt->fn((char *)pobj + pview->vt->delta, 6, 0, 0, 0, 0);
        pmurray->ploCarried = 0;
        return;
    }
    DetachMurrayObject(pmurray);
    LO *plo = *(LO **)((char *)pmurray->ploCarried + 0x180);
    if (FIsBasicDerivedFrom(plo, 0x38) != 0)
        func_00209EE0(plo);
    else
        func_001F7A68(plo, 1);
    switch (pmurray->state) {
    case 5: {
        VIEW118 *pview = (VIEW118 *)plo;
        SLOT *slot = (SLOT *)((char *)pview->vt + 0x118);
        char *self = (char *)plo + slot->delta;
        QW v = bevy_camera_follow_track_heading_weight(pmurray, 0, D_002C09E0);
        slot->fn(self, v);
        break;
    }
    case 2:
    case 4:
    case 7:
    case 8:
        {
            VIEW118 *pview = (VIEW118 *)plo;
            pview->vt->fn((char *)plo + pview->vt->delta, g_2a2dd0);
        }
        break;
    }
    pmurray->ploCarried = 0;
}
