#include "sly2.h"
#include "cplcy.h"
extern "C" void DeactivateCplcy(CPTN *);
extern "C" void DeactivateCptn(CPTN *pcptn)
{
    pcptn->ptn = 0;
    pcptn->ptnfn = 0;
    DeactivateCplcy(pcptn);
}
