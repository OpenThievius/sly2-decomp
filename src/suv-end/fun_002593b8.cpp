#include "sly2.h"
#include "emitter.h"
extern "C" EMITPARAMS D_002BDE70;
extern "C" EMITPARAMS B_002DE720;
extern "C" EMITB *func_002590F0(EMITTER *, int);

extern "C" EMITPARAMS *func_002593B8(EMITTER *pemitter, int ensk)
{
    EMITB *pemitb = func_002590F0(pemitter, ensk);
    if (ensk == 1 && pemitb->emitpk == -1) {
        pemitb->emitpk = ensk;
        pemitb->params = D_002BDE70;
    }
    if (pemitb->emitpk != 1)
        return &B_002DE720;
    return &pemitb->params;
}
