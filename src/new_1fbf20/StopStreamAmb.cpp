#include "streamamb.h"
extern "C" void func_00233088(int, int, int, int, int, int, int);
extern "C" void StopStreamAmb(STREAMAMB *pamb)
{
    func_00233088(0x524B5553, 2, pamb->voice, 0, 0, 0, 0);
}
