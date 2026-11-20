#include "sly2.h"
#include "so.h"
struct MQ;
struct OXA;
struct LINK { MQ *pmq; LINK *next; MQ **ppmq; SO *pso; };
struct OXA { char pad[0x58]; OXA *next; char pad2[4]; SO *owner; LINK *first; MQ *pmqList; char pad3[4]; u64 grf; };
struct SWXP { char pad[0x3D34]; OXA *head; };
struct SW;
struct XP { char pad[0xEC]; OXA *poxa; };
extern "C" void func_00133E30(void *);
extern "C" void UpdateSwAaox__FP2SW(void *);
extern "C" void CStackFrame_Construct(void *);
extern "C" void CStackFrame_Destructor(void *, int);
extern "C" void FreeSwMqList__FP2SWP2MQ(void *, MQ *);
extern "C" MQ *PxpMarkSwContactsRoot(void *, OXA *, OXA *);
extern "C" void RemoveDlEntry(void *, void *);
extern "C" void func_001F5078(SO *);

extern "C" void RecalcSwXpAll(SWXP *sw)
{
    char frame[16];
    OXA *list[0x300];
    int count = 0;
    func_00133E30(sw);
    UpdateSwAaox__FP2SW(sw);
    CStackFrame_Construct(frame);
    OXA *oxa = sw->head;
    if (oxa) {
        do {
            u64 grf = oxa->grf;
            if (!(grf & 4)) {
                grf |= 0x10;
                oxa->grf = grf;
                if (!(grf & 8)) {
                    oxa->grf = grf | 8;
                    list[count++] = oxa;
                }
                LINK *link = (LINK *)((DL *)((char *)oxa + 0x64))->head;
                if (link) {
                    OXA **slot = &list[count];
                    do {
                        OXA *other = ((SO *)((void **)link)[3])->poxa;
                        u64 grfOther = other->grf;
                        if (!(grfOther & 0x10)) {
                          if (!(grfOther & 4)) {
                            if (!(grfOther & 8)) {
                                count++;
                                other->grf = grfOther | 8;
                                *slot = other;
                                slot++;
                            }
                            oxa->owner->Slot54(other->owner);
                            other->owner->Slot54(oxa->owner);
                            MQ *old = link->pmq;
                            FreeSwMqList__FP2SWP2MQ(sw, old);
                            MQ *mq = PxpMarkSwContactsRoot(sw, oxa, other);
                            link->pmq = mq;
                            *link->ppmq = mq;
                            if (old || link->pmq) {
                                if (!oxa->owner->FIsLocked())
                                    func_001F5078(oxa->owner);
                                if (!other->owner->FIsLocked())
                                    func_001F5078(other->owner);
                            }
                          }
                        }
                        link = link->next;
                    } while (link);
                }
            }
            oxa = oxa->next;
        } while (oxa);
        oxa = sw->head;
        if (oxa) {
            do {
                oxa->grf &= ~0x10UL;
                oxa->owner->Slot54(0);
                FreeSwMqList__FP2SWP2MQ(sw, oxa->pmqList);
                oxa->pmqList = 0;
                oxa->owner->Slot59();
                oxa->grf &= ~2UL;
                RemoveDlEntry(&sw->head, oxa);
                oxa = sw->head;
            } while (oxa);
        }
    }
    for (int index = 0; index < count; index++) {
        oxa = list[index];
        oxa->grf &= ~8UL;
        oxa->owner->Slot58();
    }
    CStackFrame_Destructor(frame, 2);
}
