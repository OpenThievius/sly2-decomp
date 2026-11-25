#include "sly2.h"
#include "goals.h"
#include "step.h"
/* class 0xC2 (GOALPARTNERFOLLOW, goals.h) as this caller fills it: a word at 0x30 (the leader slot) and a quadword at 0x40 */
struct PARTNERFOLLOWSTART : GOAL {
    s32 field_0x30;
    u8 unknown_0x34[0xC];
    QW pos;
};
extern "C" void GoalStack_Clear(GOALSTACK *);
extern "C" PARTNERFOLLOWSTART *func_00205438(STEP *, int);
extern "C" void func_00142540(STEP *self, int arg1, QW arg2)
{
    GoalStack_Clear(self->pgoalstack());
    if (arg1 != 0) {
        PARTNERFOLLOWSTART *go = func_00205438(self, 0xC2);
        go->field_0x30 = arg1;
        go->pos = arg2;
        go->Activate();
    }
}
