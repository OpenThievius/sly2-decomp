#include "sly2.h"
#include "blot.h"
#include "jt.h"
#include "sw.h"
struct METER { u8 unknown_0x0[0x20]; float fill; float fillCopy; float power; float powerCopy; int zero; JT *target; BLOT *blot; int ids[5]; };
static inline void SetMeterIds(METER *self, int first, int second, int third, int fourth, int fifth)
{
    self->ids[0] = first;
    self->ids[1] = second;
    self->ids[2] = third;
    self->ids[3] = fourth;
    self->ids[4] = fifth;
}
extern "C" {
extern SW B_003DD490;
BLOT *PloFindSwObject_thunk(SW *, int, int, int);
PO *PpoSwFocusBase(SW *);
int FIsBasicDerivedFrom(void *, int);
int GetJtPower(JT *);
void SeekBlotLabel(float, BLOT *, int);
void func_00213B00(BLOT *, int);
void InitMeter(METER *meter)
{
    BLOT *blot = PloFindSwObject_thunk(&B_003DD490, 0x405, 0x36B, 0);
    meter->zero = 0;
    meter->target = 0;
    meter->blot = blot;
    PO *focus = PpoSwFocusBase(&B_003DD490);
    if (focus != 0 && FIsBasicDerivedFrom(focus, 0x34) != 0)
        meter->target = (JT *)focus;
    if (meter->target == 0) {
        meter->power = meter->powerCopy = meter->fill = meter->fillCopy = 0.0f;
    } else {
        float fill = (float)*meter->target->pnHealth / (float)meter->target->field_0xDFC;
        meter->fillCopy = fill;
        meter->fill = fill;
        float power = (float)GetJtPower(meter->target) / (float)meter->target->nPowerMax;
        meter->powerCopy = power;
        meter->power = power;
        if (FIsBasicDerivedFrom(meter->target, 0x37) != 0)
            SetMeterIds(meter, 0x347, 0x348, 0x349, 0x34A, 0x34B);
        else if (FIsBasicDerivedFrom(meter->target, 0x36) != 0)
            SetMeterIds(meter, 0x342, 0x343, 0x344, 0x345, 0x346);
        else
            SetMeterIds(meter, 0x33D, 0x33E, 0x33F, 0x340, 0x341);
        BLOT *target = meter->blot;
        if (target != 0) {
            target->Select(meter->ids[0]);
            func_00213B00(meter->blot, 0x34F);
            func_00213B00(meter->blot, 0x350);
            SeekBlotLabel(1.0f - meter->fill, meter->blot, 0x34F);
            SeekBlotLabel(1.0f - meter->power, meter->blot, 0x350);
        }
    }
}
}
