#include "sw.h"
#include "blot.h"
extern "C" {
void func_00212A30(BLOT *);
void ShowCoinBlot(SW *psw) {
    BLOT *target = (BLOT *)psw->ahudblot[1].plo;
    if (target != 0) {
        target->Select(-1);
        func_00212A30(target);
    }
}
}
