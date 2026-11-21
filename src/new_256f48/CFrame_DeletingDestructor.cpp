#include "cref.h"
struct VARB { int count; int pad4; int pad8; CRef ref; VARB *next; };
struct FRAME { int count; int pad4; int pad8; FRAME *parent[4]; VARB *pvarb; };
struct SLOTHEAP;
extern "C" {
void VarbPtr_Destructor(VARB **, int);
void UnlinkVarbNode(VARB *);
void UnlinkFrameNode(FRAME *);
void FreeSlotheapPv(SLOTHEAP *, void *);
void func_002572E0(FRAME **, int);
extern SLOTHEAP B_004520D0;
extern SLOTHEAP B_004520F8;
}
extern "C" void CFrame_DeletingDestructor(FRAME *pframe, unsigned grf)
{
    VARB *pvarb = pframe->pvarb;
    if (pvarb != 0) {
        if (--pvarb->count == 0) {
            VarbPtr_Destructor(&pvarb->next, 2);
            pvarb->ref.Decref();
            UnlinkVarbNode(pvarb);
            FreeSlotheapPv(&B_004520D0, pvarb);
        }
    }
    unsigned fFree = grf & 1;
    FRAME **ppframeBegin = pframe->parent;
    if (ppframeBegin != 0) {
        FRAME **ppframe = ppframeBegin + 4;
        if (ppframeBegin != ppframe) {
            do {
                --ppframe;
                func_002572E0(ppframe, 0);
            } while (ppframeBegin != ppframe);
        }
    }
    UnlinkFrameNode(pframe);
    if (fFree != 0)
        FreeSlotheapPv(&B_004520F8, pframe);
}
