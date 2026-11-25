#include "sly2.h"
struct SAA_base {
    u8 unknown_0x0[0xC];
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Update();
};
struct SAA : SAA_base {
    u8 unknown_0x10[0x30 - 0x10];
    /* 0x30 */ int flag;
    u8 unknown_0x34[0x40 - 0x34];
    /* 0x40 */ SAA *next;
};
extern "C" {
extern SAA *B_003E159C;
int FUpdatableSaa__FP3SAA(SAA *);
void UpdateSaas(void)
{
    char frame[0x10] __attribute__((aligned(16))); // retail frame shows a dead 0x10 area
    SAA *saa = B_003E159C;
    while (saa && saa->flag == 0) {
        if (FUpdatableSaa__FP3SAA(saa) != 0) saa->Update();
        saa = saa->next;
    }
}
}
