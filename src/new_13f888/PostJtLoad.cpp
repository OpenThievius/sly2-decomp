#include "sly2.h"
#include "alloc.h"
#include "jt.h"
struct UL { unsigned long v; } __attribute__((packed));
struct SwWorld { char pad0[0x3BF4]; unsigned flags; char pad3bf8[0x3D58 - 0x3BF8]; int serial; };
struct ObjectEntry { LO *object; int pad; };
struct SlotEntry { short adjust; short pad; void (*function)(void *, ...); };
struct JtBody { char pad0[0x94]; int flag; };
extern "C" {
void PostStepLoad(JT *);
void SetSoProperties(void *, int, void *);
void func_001959C0(void *);
void LoadAttach(void *);
void func_0019F3F0(void *);
void PostJtLoadZap__FP2JT(void *);
void PostBinocLoad(void *);
void CarryThrow_EnsureBlends(void *);
void PostJtLoadPipe(void *);
int CploFindSwObjects_thunk(SwWorld *, int, int, void *, int, void **);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
void bevy_player_p18_gadget_refill(void *, int);
int PalertEnsure(void *);
void SetSoMass__FP2SOf(void *, float);
QW PosLoWorld(void *);
char *PmatLoWorld(void *);
void QueueSwCallback(SwWorld *, void *, unsigned long, int);
void LoadJtGadgetSlots(JT *);
extern SwWorld B_003DD490;
extern char D_002BC9F0[];
extern const UL RO_002A4D10;
}
extern "C" void PostJtLoad(JT *self)
{
    void *found[16];
    ALLOCREQ request;
    QW saved[3];
    char *base = (char *)self;
    PostStepLoad(self);
    SetSoProperties(self, 0x35, D_002BC9F0);
    func_001959C0(base + 0x2C0);
    LoadAttach(base + 0x4C0);
    func_0019F3F0(base + 0x9E0);
    PostJtLoadZap__FP2JT(base + 0xDF0);
    PostBinocLoad(base + 0xF00);
    CarryThrow_EnsureBlends(base + 0x11B0);
    PostJtLoadPipe(base + 0xF50);
    int count = CploFindSwObjects_thunk(&B_003DD490, 0x401, 0x2AB, self, 0x10, found);
    if (count != 0) {
        ALLOCREQ *pointer = &request;
        pointer->cb = count * 8;
        *(int *)(base + 0x1094) = count;
        pointer->cbAlign = 0x10;
        ObjectEntry *objects = (ObjectEntry *)PvAllocSwClearImpl__Fi(pointer);
        *(ObjectEntry **)(base + 0x1090) = objects;
        for (int index = 0; index < count; index++) {
            LO *object = (LO *)found[index];
            (*(ObjectEntry **)(base + 0x1090))[index].object = object;
            (*(ObjectEntry **)(base + 0x1090))[index].object->Remove();
        }
    }
    SlotEntry *slot = (SlotEntry *)(*(char **)(base + 0xC) + 0x278);
    slot->function((char *)self + slot->adjust, 0);
    self->Slot104();
    LoadJtGadgetSlots(self);
    bevy_player_p18_gadget_refill(self, B_003DD490.flags & 4);
    *(int *)(base + 0x1088) = PalertEnsure(self);
    SetSoMass__FP2SOf(self, 0.25f);
    if (((JtBody *)*(char **)(base + 0x54))->flag == 0) {
        QW position = PosLoWorld(self);
        char *matrix = PmatLoWorld(self);
        saved[0] = *(QW *)matrix;
        saved[1] = *(QW *)(matrix + 0x10);
        saved[2] = *(QW *)(matrix + 0x20);
        char *body = *(char **)(base + 0x54);
        memset(body, 0, 0x40);
        *(float *)(body + 0x3C) = 1.0f;
        *(float *)(body + 0x28) = 1.0f;
        *(float *)(body + 0x14) = 1.0f;
        *(float *)(body + 0x0) = 1.0f;
        int serial = B_003DD490.serial + 1;
        B_003DD490.serial = serial;
        *(int *)(*(char **)(base + 0x54) + 0xA4) = serial;
        self->UpdateXfWorldHierarchy();
        self->TranslateToPos(position);
        self->Slot30(saved);
    }
    QueueSwCallback(&B_003DD490, self, RO_002A4D10.v, 0);
}
