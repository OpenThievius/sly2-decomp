#include "emitter.h"
struct B8 { char b[8]; };
struct B12 { B8 lo; int hi; };
extern "C" {
EMITPARAMS *func_002593B8(EMITTER *, int);
extern const B8 D_002BDE50;
extern const int g_2bde58;
extern const B12 D_002BDE60;
}
extern "C" void func_00259608(EMITTER *pemitter, int ript)
{
    EMITPARAMS *pript = func_002593B8(pemitter, 1);
    if (pript->kind == ript || pript->kind != -1)
        return;
    pript->kind = ript;
    switch (ript) {
    case 2:
        *(B8 *)&pript->payload = D_002BDE50;
        break;
    case 3:
        pript->payload = g_2bde58;
        break;
    case 8:
        *(B12 *)&pript->payload = D_002BDE60;
        break;
    }
}
