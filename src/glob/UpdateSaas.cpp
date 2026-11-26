#include "sly2.h"
#include "saa.h"
extern "C" {
extern SAA *B_003E159C;
int FUpdatableSaa__FP3SAA(SAA *);
void UpdateSaas(void)
{
    char frame[0x10] __attribute__((aligned(16))); // retail frame shows a dead 0x10 area
    SAA *saa = B_003E159C;
    while (saa && saa->owner == 0) {
        if (FUpdatableSaa__FP3SAA(saa) != 0) saa->Update();
        saa = saa->next;
    }
}
}
