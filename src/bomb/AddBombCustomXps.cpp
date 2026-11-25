#include "bomb.h"
#include "oxa.h"
#include "geom.h"
extern "C" char B_003DD490[];
extern "C" void func_001F5990(void *);
extern "C" void PxpAdd(float, void *, void *, void *, QW, QW, int, void *, void *, void *);

void AddBombCustomXps(BOMB *bomb, GEOM *other, int a2, void *a3, void *a4, void *ppxpFirst)
{
    func_001F5990(bomb);
    if (bomb->fCustom == 0) return;
    BOMBXP *xp = bomb->axp;
    for (; xp < bomb->axp + bomb->cXp; xp++) {
        if (xp->pso == other->pso->poxa->owner) {
            PxpAdd(xp->dist, B_003DD490, bomb->ageom, other, xp->pos, xp->normal, 9, 0, 0, ppxpFirst);
            return;
        }
    }
}
