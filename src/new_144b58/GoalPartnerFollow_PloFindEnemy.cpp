// SPDX-License-Identifier: GPL-3.0-or-later
#include "ps2inline.h"
#include "vu0inline.h"
#include "sly2.h"
#include "jt.h"
#include "stepguard.h"
#include "goal.h"
typedef STEPGUARD ENT;
struct LIST { u8 unknown_0x0[0x28]; int count; ENT *items[1]; };
struct POLY { float c0, c1, c2; };
struct SELF : GOAL { void *ptarget; u8 unknown_0x34[0x5C]; ENT *penemy; };
struct LOCALS { ENT *best; };
extern float RO_002A4E30;
extern POLY RO_002BD300;
extern POLY RO_002BD310;
extern POLY RO_002BD320;
extern "C" int FIsGuardInSgs(void *, int);
extern "C" u64 GrfsgsFromSgs(int);
extern "C" LIST *PalertFind(void *);
extern "C" QW PosLoWorld(void *);
static inline float Distance(QW pos, QW other)
{
    return LaneX(SqrtX(SquaredLength(VectorSub(pos, other))));
}
extern "C" ENT *GoalPartnerFollow_PloFindEnemy(SELF *self)
{
    LOCALS loc;
    QW pos;
    int index = 0;
    float best_distance = RO_002A4E30;
    loc.best = 0;
    PosLoWorld(self->pstep);
    pos = PosLoWorld(self->ptarget);
    u64 mask = GrfsgsFromSgs(7) | GrfsgsFromSgs(0x10) | GrfsgsFromSgs(0x16) | GrfsgsFromSgs(0x17) | GrfsgsFromSgs(0x2A) | GrfsgsFromSgs(0x2B);
    LIST *list = (LIST *)((JT *)self->pstep)->field_0x1088;
    if (list->count > 0) {
        ENT **pentry = list->items;
        do {
            ENT *ent = *pentry;
            if ((mask & ent->grfsgs) == 0) {
                QW other = PosLoWorld(ent);
                ENT *enemy = self->penemy;
                float distance = Distance(pos, other);
                if (ent == enemy)
                    distance = RO_002BD300.c0 + distance * (RO_002BD300.c1 + distance * RO_002BD300.c2);
                if (FIsGuardInSgs(ent, 3) != 0)
                    distance = RO_002BD320.c0 + distance * (RO_002BD320.c1 + distance * RO_002BD320.c2);
                if (distance < best_distance) {
                    loc.best = ent;
                    best_distance = distance;
                }
            }
            index += 1;
            pentry += 1;
        } while (index < list->count);
    }
    LIST *alert = PalertFind(self->ptarget);
    if (alert != 0) {
        index = 0;
        if (index < alert->count) {
        ENT **pentry = alert->items;
        do {
            ENT *ent = *pentry;
            if ((mask & ent->grfsgs) == 0) {
                QW other = PosLoWorld(ent);
                ENT *enemy = self->penemy;
                float distance = Distance(pos, other);
                distance = RO_002BD310.c0 + distance * (RO_002BD310.c1 + distance * RO_002BD310.c2);
                if (ent == enemy)
                    distance = RO_002BD300.c0 + distance * (RO_002BD300.c1 + distance * RO_002BD300.c2);
                if (FIsGuardInSgs(ent, 3) != 0)
                    distance = RO_002BD320.c0 + distance * (RO_002BD320.c1 + distance * RO_002BD320.c2);
                if (distance < best_distance) {
                    loc.best = ent;
                    best_distance = distance;
                }
            }
            index += 1;
            pentry += 1;
        } while (index < alert->count);
        }
    }
    return loc.best;
}
