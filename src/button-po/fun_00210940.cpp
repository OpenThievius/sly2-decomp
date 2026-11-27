#include "sw.h"
extern "C" void *PloFindSwObject_thunk(SW *, int, int, int);
void func_00210940(SW *psw)
{
    psw->ppool = PloFindSwObject_thunk(psw, 5, 0x620, 0);
}
