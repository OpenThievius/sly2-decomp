#include "jsg.h"
extern "C" void InitLo(JSG *);
extern "C" void InitDl__FP2DLi(DL *, int);
extern "C" void InitJsg(JSG *jsg)
{
    InitLo(jsg);
    jsg->cjsgeMax = -1;
    InitDl__FP2DLi(&jsg->dlSeqnode, 0xE4);
}
