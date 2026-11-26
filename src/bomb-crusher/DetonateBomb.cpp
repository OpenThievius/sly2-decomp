#include "sly2.h"

#include "vu0inline.h"
#include "ps2inline.h"
#include "bomb.h"
#include "expl.h"
#include "wkr.h"
#include "sw.h"
/* the weapon record DetonateBomb sends, with a quadword past WKR's 0x60 bytes: the scale it measured the push with (one reader, so a local struct) */
struct BOMBWKR : WKR { QW scale; };
struct Frame_13B860 { u8 unknown_0x0[0x10]; };
struct Phit_13B860 { u8 unknown_0x0[0x54]; int f54; };
struct Link_13B860 { u8 unknown_0x0[0x14]; void **f14; };
extern "C" {
void CStackFrame_Construct(Frame_13B860 *);
void CStackFrame_Destructor(Frame_13B860 *, int);
int FIsBasicDerivedFrom(void *, int);
void GetBombVictims(BOMB *, int *, void ***);
SO *PaloAbsorbWkr(WKR *);
Phit_13B860 *PhitfxSpawn(int, QW, void *);
QW PosLoWorld(void *);
void PrepareBombDetonation(BOMB *, QW, QW);
extern SW B_003DD490;
extern int D_002BC9E0;
extern QW g_2a2dc0;
extern float RO_002A4B1C;
void DetonateBomb(BOMB *self) {
    Frame_13B860 frame;
    int count;
    void **victims;
    if ((int)(self->grfo >> 60) & 1) {
        PrepareBombDetonation(self, PosLoWorld(self), g_2a2dc0);
        if (self->field_0x164 == 0) {
            int index = 0;
            CStackFrame_Construct(&frame);
            GetBombVictims(self, &count, &victims);
            if (count > 0) {
                do {
                    void *victim = victims[index];
                    BOMBWKR msg;
                    memset(&msg, 0, 0x60);
                    msg.grftak = self->field_0x1EC;
                    msg.damage = self->field_0x1F0;
                    msg.pos = self->pos180;
                    msg.psoSource = self;
                    msg.ploTarget = (LO *)victim;
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
                    msg.vel = VectorScaleX(direction, scale);
                    msg.scale = scale;
                    PaloAbsorbWkr(&msg);
                } while (index < count);
            }
            CStackFrame_Destructor(&frame, 2);
        }
        self->TranslateToPos(self->pos180);
        self->Slot30(self->field_0x190);
        self->Slot35(self->field_0x1C0);
        self->Slot36(self->field_0x1D0);
        /* BOMB::pbombOther is an explosion: it is called through EXPL's slot 51 with an EXPLSO */
        EXPL *pexpl = (EXPL *)self->pbombOther;
        if (pexpl != 0) {
            EXPLSO explso;
            explso.grfexpl = 9;
            explso.palo = (ALO *)self;
            explso.g = self->field_0x16C;
            explso.uPercent = self->radius;
            pexpl->ExplodeExplso(&explso);
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
            PhitfxSpawn(B_003DD490.field_0x402C, PosLoWorld(self), owner)->f54 = 1;
        }
        self->Remove();
        self->field_0x174 = 0;
        self->tDetonate = RO_002A4B1C;
        self->HandleSpliceEvent(5, 0, 0, 0, 0);
    }
}
}
