#include "sly2.h"
#include "alloc.h"
#include "jt.h"
#include "xf.h"
#include "sw.h"
struct UL { u64 v; } __attribute__((packed));
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
int CploFindSwObjects_thunk(SW *, int, int, void *, int, void **);
void *PvAllocSwClearImpl__Fi(ALLOCREQ *);
void bevy_player_p18_gadget_refill(void *, int);
int PalertEnsure(void *);
void SetSoMass__FP2SOf(void *, float);
QW PosLoWorld(void *);
QW *PmatLoWorld(void *);
void QueueSwCallback(SW *, void *, u64, int);
void LoadJtGadgetSlots(JT *);
extern SW B_003DD490;
extern char D_002BC9F0[];
extern const UL RO_002A4D10;
}
extern "C" void PostJtLoad(JT *self)
{
    void *found[16];
    ALLOCREQ request;
    QW saved[3];
    PostStepLoad(self);
    SetSoProperties(self, 0x35, D_002BC9F0);
    func_001959C0(self->PvJmp());
    LoadAttach(self->PvAttach());
    func_0019F3F0(self->PvPart9E0());
    PostJtLoadZap__FP2JT(self->PvZap());
    PostBinocLoad(self->PvBinoc());
    CarryThrow_EnsureBlends(self->PvCarry());
    PostJtLoadPipe(self->PvPipe());
    int count = CploFindSwObjects_thunk(&B_003DD490, 0x401, 0x2AB, self, 0x10, found);
    if (count != 0) {
        ALLOCREQ *pointer = &request;
        pointer->cb = count * 8;
        self->cloentry = count;
        pointer->cbAlign = 0x10;
        JTLOENTRY *objects = (JTLOENTRY *)PvAllocSwClearImpl__Fi(pointer);
        self->aloentry = objects;
        for (int index = 0; index < count; index++) {
            LO *object = (LO *)found[index];
            self->aloentry[index].plo = object;
            self->aloentry[index].plo->Remove();
        }
    }
    self->SetPlayable(0);
    self->Slot104();
    LoadJtGadgetSlots(self);
    bevy_player_p18_gadget_refill(self, B_003DD490.loadreq.grf & 4);
    self->field_0x1088 = (GADGETSTATE *)PalertEnsure(self);
    SetSoMass__FP2SOf(self, 0.25f);
    if (self->axf->dof == 0) {
        QW position = PosLoWorld(self);
        QW *matrix = PmatLoWorld(self);
        saved[0] = matrix[0];
        saved[1] = matrix[1];
        saved[2] = matrix[2];
        XF *body = self->axf;
        memset(body, 0, 0x40);
        body->mat.mat[3][3] = 1.0f;
        body->mat.mat[2][2] = 1.0f;
        body->mat.mat[1][1] = 1.0f;
        body->mat.mat[0][0] = 1.0f;
        int serial = B_003DD490.generation + 1;
        B_003DD490.generation = serial;
        self->axf->generation = serial;
        self->UpdateXfWorldHierarchy();
        self->TranslateToPos(position);
        self->Slot30(saved);
    }
    QueueSwCallback(&B_003DD490, self, RO_002A4D10.v, 0);
}
