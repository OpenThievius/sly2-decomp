#include "types.h"
#include "blot.h"
struct OBJ {
    u8 unknown_0x0[0x40]; int tagged;
    u8 unknown_0x44[0x68 - 0x44]; OBJ *owner;
    u8 unknown_0x6C[0x94 - 0x6C]; int cdeps; int *deps; u8 unknown_0x9C[4]; int cmembers; OBJ **members;
    u8 unknown_0xA8[0xB0 - 0xA8]; int seqA; int seqB; BLOT *vB8; BLOT *vBC; OBJ *pick; int state; float timer;
};
extern "C" {
void ClearHandsOff(void *, int);
int FTaskComplete(int);
void SetHandsOff(void *, int);
void func_001A6CA8(OBJ *, int);
void func_00213B00(BLOT *, int);
extern char B_003DD490[];
extern float g_2dded0[];
void SetJobEndSequence(OBJ *self, int arg1) {
    if (self->state == arg1) return;
    if (self->state == 0) {
        self->pick = 0;
        for (int index = 0; index < self->owner->cmembers; index++) {
            OBJ *member = self->owner->members[index];
            if (member->state != 0) {
                self->pick = member;
                break;
            }
        }
        if (self->pick != 0) {
            int dep;
            for (dep = 0; dep < self->pick->cdeps; dep++) {
                int other = self->pick->deps[dep];
                if (other == (sptr)self->owner) continue;
                if (FTaskComplete(other) == 0) {
                    self->pick = 0;
                    break;
                }
            }
        }
        func_001A6CA8(self, 1);
        {
            int raw = self->tagged;
            if ((raw ^ 1) & 1)
                *(int *)raw = *(int *)raw | 0x102;
            else
                self->tagged = raw | 0x102;
        }
        SetHandsOff(B_003DD490 + 0, 2);
    }
    self->state = arg1;
    self->timer = g_2dded0[0];
    switch (arg1) {
    case 0: {
        BLOT *objC = self->vBC;
        if (objC != 0) {
            objC->Hide();
        }
        BLOT *objB = self->vB8;
        if (objB != 0) {
            objB->Hide();
        }
        func_001A6CA8(self, 2);
        {
            int raw = self->tagged;
            if ((raw ^ 1) & 1)
                *(int *)raw = *(int *)raw & ~0x102;
            else
                self->tagged = raw & ~0x102;
        }
        ClearHandsOff(B_003DD490, 2);
        return;
    }
    case 1: {
        BLOT *objB = self->vB8;
        objB->Select(-1);
        func_00213B00(self->vB8, self->seqA);
        return;
    }
    case 3: {
        BLOT *objC = self->vBC;
        objC->Select(-1);
        return;
    }
    case 2:
        func_00213B00(self->vB8, self->seqB);
        break;
    }
}
}
