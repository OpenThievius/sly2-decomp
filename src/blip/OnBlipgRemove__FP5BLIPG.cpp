#include "sly2.h"
#include "dl.h"
struct BLIP;
struct BLIPG { char pad[0x10]; int parent; char pad1[0x448 - 0x14]; DL blips; };
extern DL B_002DEAF0;
void RemoveBlip(BLIP *pblip);
extern "C" void RemoveLoHierarchy(BLIPG *);
extern "C" void func_001A57A8(BLIPG *);
extern "C" void func_001A53E0(BLIPG *);
extern "C" void AppendDlEntry(DL *, BLIPG *);

void OnBlipgRemove(BLIPG *pblipg)
{
    DLI iterator;
    PushDli(&iterator, &pblipg->blips);
    BLIP *pblip;
    for (pblip = (BLIP *)PvStep(&iterator); pblip != 0; pblip = (BLIP *)PvStep(&iterator))
        RemoveBlip(pblip);
    RemoveLoHierarchy(pblipg);
    func_001A57A8(pblipg);
    if (pblipg->parent == 0)
        func_001A53E0(pblipg);
    AppendDlEntry(&B_002DEAF0, pblipg);
    PopDli(&iterator);
}
