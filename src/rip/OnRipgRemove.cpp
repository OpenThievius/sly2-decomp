#include "sly2.h"
#include "dl.h"
#include "sw.h"
#include "rip.h"
extern SW B_003DD490;
extern "C" void RemoveRip(char *);
extern "C" void RemoveSoLoHierarchy(RIPG *);
extern "C" void FreeSwPoxa(SW *, OXA *);
extern "C" void func_001A57A8(RIPG *);
extern "C" void func_001A53E0(RIPG *);
extern "C" void *PdlFromSwCid(SW *, int);
extern "C" void RemoveSlEntry(void *, RIPG *);
extern "C" void FreeSlotheapPv(void *, RIPG *);


void OnRipgRemove(RIPG *ripg)
{
    DLI iterator;
    PushDli(&iterator, &ripg->rips);
    char *item;
    for (item = (char *)PvStep(&iterator); item != 0; item = (char *)PvStep(&iterator))
        RemoveRip(item);
    if ((PRIPG *)ripg == B_003DD490.pripgCached)
        B_003DD490.pripgCached = 0;
    RemoveSoLoHierarchy(ripg);
    if (ripg->poxa != 0) {
        FreeSwPoxa(&B_003DD490, ripg->poxa);
        ripg->poxa = 0;
    }
    func_001A57A8(ripg);
    RemoveSlEntry(PdlFromSwCid(&B_003DD490, 0x57), ripg);
    if (ripg->psoParent == 0)
        func_001A53E0(ripg);
    FreeSlotheapPv(&B_003DD490.slotheapRipg, ripg);
    PopDli(&iterator);
}
