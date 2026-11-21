#include "so.h"
extern "C" void RemoveSoGeomsFromOxa(SO *);
extern "C" void AddSoGeomsToOxa(SO *);
extern "C" void func_001A5B80(SO *, int, SO *);
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
#define FLAG (0x8000UL << 41)
void UpdateSoRoot(SO *pso, SO *psoStop, SO *psoOther)
{
    VECTOR local;
    func_001A5B80(pso, (sptr)psoStop, psoOther);
    LO *plo;
    for (plo = (LO *)pso->dlChild.head; plo; plo = plo->ploNext)
        plo->Slot13((sptr)psoStop, psoOther);
    if (pso->cgeom != 0) {
        plo = pso;
        if (!(pso->grfo & FLAG)) {
            while (plo != psoStop) {
                plo = plo->psoParent;
                if (plo->grfo & FLAG) return;
            }
            SO *other = psoOther;
            while (other && !(other->grfo & FLAG)) other = other->psoParent;
            SO *ancestor = pso->psoParent;
            while (ancestor && !(ancestor->grfo & FLAG)) ancestor = ancestor->psoParent;
            if (!other && !ancestor) {
                RemoveSoGeomsFromOxa(pso);
                AddSoGeomsToOxa(pso);
            }
        }
    }
}
