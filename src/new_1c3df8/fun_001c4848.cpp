#include "sw.h"
#include "emitter.h"
#include "alloc.h"
extern "C" {
EMITB *PemitbEnsureEmitter(EMITTER *, int);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);

void func_001C4848(SW *psw, EMITTER *pemitter) {
    unsigned count = psw->cemitter;
    if (count < 4U) {
        psw->aemitter[count] = pemitter;
        psw->cemitter = count + 1;
        EMITB *pemitb = PemitbEnsureEmitter(pemitter, 1);
        if (pemitb->pinfo == 0) {
            ALLOCREQ request;
            request.cb = 0x14;
            request.cbAlign = 0x10;
            pemitb->pinfo = (EMITBINFO *)PvAllocSwClearImpl__Fi(&request);
        }
    }
}
}
