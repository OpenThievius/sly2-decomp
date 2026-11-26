#include "sly2.h"
#include "jt.h"
#include "phys.h"
struct Link { u8 unknown_0x0[0x10]; void *pzone; };
struct Zone { u8 unknown_0x0[0x18]; int oid; };
#include "goals.h"
extern "C" {
Zone *GoalPartnerFollow_PpathzoneTarget(GOALPARTNERFOLLOW *);
int FIsBasicDerivedFrom(void *, int);
QW PosLoWorld(void *);
int FPosFreeInPathzone(Zone *, QW, int);
int FFindSurfaceAlongUp(float, float, QW *, int, int);
}
int func_001459C0(GOALPARTNERFOLLOW *pgoal)
{
    Zone *pzone = GoalPartnerFollow_PpathzoneTarget(pgoal);
    if (pzone == 0)
        return 0;
    PHYS *pphys = pgoal->pstep->pphys;
    Link *plink = 0;
    if (pphys)
        plink = (Link *)pphys->plink;
    void *pown = 0;
    if (plink)
        pown = plink->pzone;
    if (pzone == pown)
        return 0;
    if (pzone->oid == 0x2CA)
        return 0;
    if (FIsBasicDerivedFrom(pgoal->ploLeader, 0x34)) {
        if (((JT *)pgoal->ploLeader)->jmpState != -1)
            return 0;
    }
    QW pos = PosLoWorld(pgoal->ploLeader);
    if (FPosFreeInPathzone(pzone, pos, 0)) {
        if (FFindSurfaceAlongUp(100.0f, -150.0f, &pos, 0, 0)) {
            pgoal->posWarp = pos;
            return 1;
        }
    }
    return 0;
}
