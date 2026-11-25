#include "vu0inline.h"
#include "ps2inline.h"
#include "sly2.h"
#include "stepguard.h"
extern "C" {
QW PosLoWorld(void *);
int FIsBasicDerivedFrom(void *, int);
int FIsGuardPriorityClass(void *, void *);
int func_002089F0(void *, void *);
int func_00208B38(void *, void *);
extern float D_FLT_002C3D70[3];
extern float D_FLT_002C3D80[3];
}
extern "C" void *func_002082D0(STEPGUARD *self)
{
    void *best = 0;
    LO *current = (LO *)self->field_0x390;
    if (current != 0 && ((int)(current->grfo >> 60) & 1)) {
        best = current;
    } else {
        float bestDistance = 3.4028235e38f;
        QW origin = PosLoWorld(self);
        for (int index = 0; index < self->psensor->centry; index++) {
            SENSORENTRY *entry = &self->psensor->aentry[index];
            LO *object = entry->plo;
            if (object == 0)
                continue;
            if (entry->state == 0) {
                if (self->mode != 0x22 && self->mode != 0x25)
                    continue;
                if (FIsBasicDerivedFrom(object, 0x38) == 0)
                    continue;
            }
            if (func_002089F0(self, object) != 0)
                continue;
            if (func_00208B38(self, object) != 0)
                return object;
            QW position = PosLoWorld(object);

            float distance = LaneX(SqrtX(SquaredLength(VectorSub(origin, position))));
            if (object == self->pbasicAlert)
                distance = D_FLT_002C3D70[0] + distance * (D_FLT_002C3D70[1] + distance * D_FLT_002C3D70[2]);
            if (self->mode == 0x22 || self->mode == 0x25) {
                if (FIsBasicDerivedFrom(object, 0x38) != 0)
                    distance = D_FLT_002C3D80[0] + distance * (D_FLT_002C3D80[1] + distance * D_FLT_002C3D80[2]);
            }
            if (FIsGuardPriorityClass(self, object) != 0) {
                if (best != 0 && FIsGuardPriorityClass(self, best) == 0) {
                    bestDistance = distance;
                    best = object;
                    continue;
                }
            } else if (best != 0 && FIsGuardPriorityClass(self, best) != 0) {
                continue;
            }
            if (distance < bestDistance) {
                bestDistance = distance;
                best = object;
            }
        }
    }
    return best;
}
