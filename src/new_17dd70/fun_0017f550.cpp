#include "sohit.h"
extern "C" {
s32 FAsegaGone(s32);
s32 GetSmaCur(s32);
s32 GetSmaGoal(s32);
s32 func_0017F550(SOHIT *arg0) {
    s32 current;
    s32 difference;
    s32 result;

    if (arg0->hAsega != 0) {
        return FAsegaGone(arg0->hAsega);
    }
    result = 1;
    if (arg0->hSma != 0) {
        current = GetSmaCur(arg0->hSma);
        difference = current ^ GetSmaGoal(arg0->hSma);
        result = difference == 0;
    }
    return result;
}
}
