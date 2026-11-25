#include "crfodb.h"
#include "sw.h"
extern "C" void func_00183F50();
extern "C" SW B_003DD490;
void PostCrfodbLoad__FP6CRFODB(CRFODB* pguard)
{
    func_00183F50();
    pguard->oid = B_003DD490.oidNext++;
}
