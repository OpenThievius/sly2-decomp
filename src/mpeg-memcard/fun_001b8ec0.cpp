#include "murray.h"
#include "joy.h"
#include "types.h"
/* two words of Murray's state machine that func_001B8EC0 alone reads (the state's start time after field_0x1840, and the jumper at 0x1900
   in the part InitMurray hands to func_0020BD78): a local view of murray.h's MURRAY */
struct MURRAYJUMPVIEW {
    u8 unknown_0x0[0x1844];
    /* 0x1844 */ f32 tState;
    u8 unknown_0x1848[0xB8];
    /* 0x1900 */ s32 jumper;
};
extern "C" {
extern float g_2dded0;
extern float RO_002C0A30, RO_002C0A34;
static inline float Ld(const float *p) { return *p; }
int FAsegaGone(int);
int FJumperDone(int);
void SetMurrayState(MURRAY *, int);
void UpdateJumper(int);
void func_001B8D30(MURRAY *, int);
void func_001B8EC0(MURRAY *self) {
    int previous;
    for (;;) {
        previous = self->field_0x1840;
        switch (previous) {
        case 0:
            if ((int)self->field_0x1030 == 0 || FAsegaGone((int)self->field_0x1030) != 0) func_001B8D30(self, 1);
            break;
        case 1:
            if ((int)self->field_0x1030 == 0 || FAsegaGone((int)self->field_0x1030) != 0) {
                SetMurrayState(self, 0);
            } else if (self->field_0x1908 != 0) {
                func_001B8D30(self, 2);
            } else if (self->field_0x1AC0 == 0 && Ld(&RO_002C0A30) < g_2dded0 - ((MURRAYJUMPVIEW *)self)->tState) {
                func_001B8D30(self, 3);
            }
            break;
        case 2:
            if (((MURRAYJUMPVIEW *)self)->jumper == 0 || FJumperDone(((MURRAYJUMPVIEW *)self)->jumper) != 0) {
                if (self->field_0x1AC0 != 0) func_001B8D30(self, 0);
                else SetMurrayState(self, 0);
            } else {
                UpdateJumper(((MURRAYJUMPVIEW *)self)->jumper);
            }
            break;
        case 3:
            if ((int)self->field_0x1030 == 0 || FAsegaGone((int)self->field_0x1030) != 0) {
                SetMurrayState(self, 0);
            } else if (Ld(&RO_002C0A34) < g_2dded0 - ((MURRAYJUMPVIEW *)self)->tState) {
                JOY *target = self->pjoy;
                if (target->vjoym == 1 && target->uStick > 0.0f) SetMurrayState(self, 0);
            }
            break;
        }
        if (self->field_0x1840 != previous) { if (self->field_0x1840 != -1) continue; }
        break;
    }
}
}
