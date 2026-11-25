#include "types.h"
extern "C" {
void snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(int, int, char *, void (*)(int, u64), u64);
void snd_ResolveBankXREFS(void) {
    snd_SendIOPCommandNoWait__FiiPcPFiUl_vUl(8, 0, 0, 0, 0);
}
}
