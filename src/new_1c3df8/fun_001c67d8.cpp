#include "dprize.h"
extern "C" void InitDprize(DPRIZE *);

/* InitDprizeCharm */
void func_001C67D8(DPRIZECHARM *pcharm)
{
    InitDprize(pcharm);
    pcharm->field_0x1D8 = 45.0f;
    pcharm->field_0x1DC = 75.0f;
    pcharm->field_0x1DC = 75.0f;
    pcharm->field_0x1D0 = 250.0f;
    pcharm->field_0x1D4 = 50.0f;
    pcharm->field_0x1E4 = 0.2f;
    pcharm->field_0x1E0 = 0.65f;
    pcharm->field_0x1A0 = 0.25f;
    pcharm->healMin = 10;
    pcharm->healMax = 20;
    pcharm->waitMin = 4.0f;
    pcharm->waitMax = 5.0f;
}
