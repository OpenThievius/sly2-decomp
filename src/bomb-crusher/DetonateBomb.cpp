#include "sly2.h"

#include "vu0inline.h"
#include "ps2inline.h"
#include "bomb.h"
union W_13B860 { void *p; int i; float f; };
struct Msg_13B860 { W_13B860 w0, w4, w8, wC, w10; u8 unknown_0x14[0xC]; QW dir; QW f40; u8 unknown_0x50[0x20]; QW f70; };
struct VT_SLOT51 {
    u8 unknown_0x0[0x198]; s16 delta; s16 index; void (*fn)(void *, void *);
};
/* the object DetonateBomb messages through its vtable (slot 51 with a pointer: not the SO::PxfFromRef signature) */
struct MsgTarget_13B860 { u8 unknown_0x0[0xC]; VT_SLOT51 *vt; };
struct Frame_13B860 { u8 unknown_0x0[0x10]; };
struct Phit_13B860 { u8 unknown_0x0[0x54]; int f54; };
struct Link_13B860 { u8 unknown_0x0[0x14]; void **f14; };
extern "C" {
void CStackFrame_Construct(Frame_13B860 *);
void CStackFrame_Destructor(Frame_13B860 *, int);
int FIsBasicDerivedFrom(void *, int);
void GetBombVictims(BOMB *, int *, void ***);
int PaloAbsorbWkr(Msg_13B860 *);
Phit_13B860 *PhitfxSpawn(int, QW, void *);
QW PosLoWorld(void *);
void PrepareBombDetonation(BOMB *, QW, QW);
struct SWBOMB { u8 unknown_0x0[0x402C]; int idHitfx; };
extern SWBOMB B_003DD490;
extern int D_002BC9E0;
extern QW g_2a2dc0;
extern float RO_002A4B1C;
void DetonateBomb(BOMB *self) {
    Frame_13B860 frame;
    int count;
    void **victims;
    Msg_13B860 msg;
    if ((int)(self->grfo >> 60) & 1) {
        PrepareBombDetonation(self, PosLoWorld(self), g_2a2dc0);
        if (self->field_0x164 == 0) {
            int index = 0;
            CStackFrame_Construct(&frame);
            GetBombVictims(self, &count, &victims);
            if (count > 0) {
                do {
                    void *victim = victims[index];
                    memset(&msg, 0, 0x60);
                    msg.wC.i = self->field_0x1EC;
                    msg.w10.i = self->field_0x1F0;
                    msg.dir = self->pos180;
                    msg.w0.p = self;
                    msg.w8.p = victim;
                    QW pos = PosLoWorld(victim);
                    QW fallback = g_2a2dc0;
                    QW offset = VectorSub(pos, self->pos180);
                    QW distance = SqrtX(SquaredLength(offset));
                    if (LaneX(distance) < 0.0001f)
                        distance = fallback;
                    else
                        distance = ScaleByReciprocalX(offset, distance);
                    QW direction = distance;
                    QW scale = VectorFromWord(*(u32 *)&D_002BC9E0);
                    index++;
                    msg.f40 = VectorScaleX(direction, scale);
                    msg.f70 = scale;
                    PaloAbsorbWkr(&msg);
                } while (index < count);
            }
            CStackFrame_Destructor(&frame, 2);
        }
        self->TranslateToPos(self->pos180);
        self->Slot30(self->field_0x190);
        self->Slot35(self->field_0x1C0);
        self->Slot36(self->field_0x1D0);
        MsgTarget_13B860 *other = (MsgTarget_13B860 *)self->pbombOther;
        if (other != 0) {
            msg.w0.i = 9;
            msg.w4.p = self;
            msg.w8.f = self->field_0x16C;
            msg.wC.f = self->field_0x15C;
            other->vt->fn((char *)other + other->vt->delta, &msg);
        }
        if (self->field_0x1E0 != 0) {
            void *attacker = self->pbombOwner;
            void *owner = self;
            if (attacker != (void *)self && FIsBasicDerivedFrom(attacker, 0x70) != 0) {
                void **link = ((Link_13B860 *)attacker)->f14;
                if (link != 0) {
                    owner = ((*link) == attacker) ? (void *)self : (*link);
                }
            }
            PhitfxSpawn(B_003DD490.idHitfx, PosLoWorld(self), owner)->f54 = 1;
        }
        self->Remove();
        self->field_0x174 = 0;
        self->tDetonate = RO_002A4B1C;
        self->HandleSpliceEvent(5, 0, 0, 0, 0);
    }
}
}
