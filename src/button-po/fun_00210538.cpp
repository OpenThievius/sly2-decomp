// SPDX-License-Identifier: GPL-3.0-or-later
#include "sw.h"
#include "swfind.h"
/* the request func_00210538 hands to slot 51 of the object it finds */
struct REQ {
    unsigned grf;
    LO *ptarget;
    float g;
    u8 unknown_0xC[0x24];
    LO *pextra;
};
/* the found object's class: LO's 48 virtuals, then the two slots before the one this function calls (49 and 50) */
struct LO_REQ : LO {
    virtual void Slot49();
    virtual void Slot50();
    virtual void Request(REQ *preq);
};
void func_00210538(SW *psw, int oid, int oidTarget, int oidExtra, LO *ploContext, float g)
{
    LO_REQ *pobject = (LO_REQ *)PloFindSwObject_thunk(psw, 4, oid, ploContext);
    if (!pobject)
        return;
    REQ request;
    request.grf = 0;
    if (oidTarget != -1) {
        LO *ptarget = PloFindSwObject_thunk(psw, 4, oidTarget, ploContext);
        if (ptarget) {
            request.ptarget = ptarget;
            request.grf |= 1;
        }
    }
    if (((request.grf ^ 1) & 1) != 0) {
        request.grf |= 1;
        request.ptarget = pobject;
    }
    if (oidExtra != -1) {
        LO *pextra = PloFindSwObject_thunk(psw, 4, oidExtra, ploContext);
        if (pextra) {
            request.pextra = pextra;
            request.grf |= 0x20;
        }
    }
    if (g != 1.0f) {
        request.grf |= 0x18;
        request.g = g;
    }
    pobject->Request(&request);
}
