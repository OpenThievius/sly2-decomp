#include "emitter.h"
extern "C" void SetSuvSuvs(EMITTER *, int);
int * func_002595D0(EMITTER *pemitter, int ensk)
{
    if (ensk == 1)
        SetSuvSuvs(pemitter, 2);
    return (int *)&pemitter->pemitb->emitok;
}
