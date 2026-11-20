#include "vu0inline.h"
#include "ps2inline.h"
extern "C" {
QW PosLoWorld(void *);
int FIsBasicDerivedFrom(void *, int);
int FIsGuardPriorityClass(void *, void *);
int func_002089F0(void *, void *);
int func_00208B38(void *, void *);
extern float D_FLT_002C3D70[3];
extern float D_FLT_002C3D80[3];
}
struct ENTRY_2082D0 { void *object; int flag; int pad[2]; };
struct LIST_2082D0 { char pad[0xFC]; int count; ENTRY_2082D0 entry[1]; };
struct SELF_2082D0 {
    char pad0[0x38C];
    void *special;
    struct { char pad[0x28]; unsigned long bits; } *current;
    char pad1[0xF64 - 0x394];
    LIST_2082D0 *list;
    char pad2[0xFBC - 0xF68];
    int state;
};

extern "C" void *func_002082D0(SELF_2082D0 *self)
{
    void *best = 0;
    if (self->current != 0 && ((int)(self->current->bits >> 60) & 1)) {
        best = self->current;
    } else {
        float bestDistance = 3.4028235e38f;
        QW origin = PosLoWorld(self);
        for (int index = 0; index < self->list->count; index++) {
            ENTRY_2082D0 *entry = &self->list->entry[index];
            void *object = entry->object;
            if (object == 0)
                continue;
            if (entry->flag == 0) {
                if (self->state != 0x22 && self->state != 0x25)
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
            if (object == self->special)
                distance = D_FLT_002C3D70[0] + distance * (D_FLT_002C3D70[1] + distance * D_FLT_002C3D70[2]);
            if (self->state == 0x22 || self->state == 0x25) {
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
