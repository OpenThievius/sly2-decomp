#include "mpeg.h"
extern int func_00239450();
extern void func_002394A0();
extern void func_00254BC0();
void func_0024AC10(MPEGDEC *mpeg)
{
    int flag;
    mpeg->commandPending = 1;
    mpeg->resetDcPredictor = 0;
    flag = func_00239450();
    *(volatile unsigned *)0x1000F590 = *(volatile unsigned *)0x1000F520 | 0x10000;
    *(volatile unsigned *)0x1000B000 = 0;
    *(volatile unsigned *)0x1000B400 = 0;
    *(volatile unsigned *)0x1000D400 = 0;
    *(volatile unsigned *)0x1000F590 = *(volatile unsigned *)0x1000F520 & 0xFFFEFFFF;
    if (flag)
        func_002394A0();
    *(volatile unsigned *)0x1000B020 = 0;
    *(volatile unsigned *)0x1000B420 = 0;
    *(volatile unsigned *)0x1000D420 = 0;
    *(volatile unsigned *)0x10002010 = 0x40000000;
    func_00254BC0(0, 0);
}
