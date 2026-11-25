#include "emitter.h"
extern "C" void SetSuvSuvs(EMITTER *, int);
int * func_00259560(EMITTER *pemitter, int ensk)
{
    if (ensk == 1)
        SetSuvSuvs(pemitter, 0);
    return (int *)&pemitter->pemitb->emitok;
}
