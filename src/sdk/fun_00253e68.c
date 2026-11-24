#include "mpeg.h"
extern unsigned func_00252148(MPEGDEC *mpeg, unsigned count);
extern void func_0024FA38(MPEGDEC *mpeg, const char *message);
extern const char RO_002AC6E0[];
extern const char RO_002AC708[];
void func_00253E68(MPEGDEC *mpeg)
{
    unsigned selector;
    unsigned countHigh;
    unsigned fieldA;
    unsigned fieldB;
    unsigned fieldC;
    unsigned fieldD;
    unsigned fieldE;
    unsigned fieldF;
    unsigned fieldG;
    unsigned value;
    mpeg->field_0x858 = 1;
    /* plain access: retail fills the call's delay slot with this store */
    *(unsigned *)0x10002010 = *(unsigned *)0x10002010 & 0xFF7FFFFF;
    value = func_00252148(mpeg, 0x1C);
    countHigh = (value >> 1) & 0xFFF;
    fieldD = (value >> 17) & 0x3;
    fieldE = (value >> 13) & 0x3;
    fieldF = (value >> 15) & 0x3;
    mpeg->field_0x150 = fieldD;
    if (fieldD != 1)
        func_0024FA38(mpeg, RO_002AC6E0);
    mpeg->field_0x14C = (value >> 19) & 0x1;
    selector = value >> 20;
    value = func_00252148(mpeg, 0x10) >> 8;
    if (selector != 0x48 && selector != 0x58 && selector != 0x44)
        func_0024FA38(mpeg, RO_002AC708);
    fieldA = mpeg->field_0x134 & 0xFFF;
    fieldB = mpeg->field_0x138 & 0xFFF;
    fieldC = mpeg->field_0x144;
    fieldG = mpeg->field_0x148;
    mpeg->field_0x134 = (fieldF << 12) | fieldA;
    mpeg->field_0x138 = (fieldE << 12) | fieldB;
    mpeg->field_0x144 = fieldC + (countHigh << 18);
    mpeg->field_0x148 = fieldG + (value << 10);
}
