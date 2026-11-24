#include "sw.h"
#include "blot.h"
extern "C" void func_00212A30(BLOT *);
extern "C" void ShowClueBlot(SW *arg0)
{
    BLOT *temp_s0 = (BLOT *)arg0->ahudblot[2].plo;
    if (temp_s0 != 0) {
        temp_s0->Select(-1);
        func_00212A30(temp_s0);
    }
}
