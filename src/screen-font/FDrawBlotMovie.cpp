#include "blot.h"
extern "C" int FBlotObscured(BLOT *);
int FDrawBlotMovie(BLOT *blot)
{
    if (blot->cur == -1) return 0;
    return FBlotObscured(blot) == 0;
}
