#include "sly2.h"
#include "carrythrow.h"
extern "C" void EnsureAsegBlendDynamic(void*, int, int, void*, int, const int*, const int*, void*);
extern "C" void CarryThrow_EnsureBlends(CARRYTHROW* pcarry)
{
    EnsureAsegBlendDynamic(pcarry->pjtOwner, 0xC, 2, pcarry->ablHold, 0, 0, 0, &pcarry->pasegblHold);
    EnsureAsegBlendDynamic(pcarry->pjtOwner, 0xC, 4, pcarry->ablAim, 0, 0, 0, &pcarry->pasegblAim);
    EnsureAsegBlendDynamic(pcarry->pjtOwner, 0xC, 2, pcarry->ablThrow, 0, 0, 0, &pcarry->pasegblThrow);
}
