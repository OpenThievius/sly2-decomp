/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "sly2.h"
#include "bentley.h"
#include "ps2inline.h"
#include "vu0inline.h"

union VU_SCALE { QW q; VECTOR v; };
extern "C" {
void AddSoGravityAcceleration(BENTLEY *);
void PresetStepAccel(BENTLEY *);
void bevy_player_p18_gadget_glide_force(void *);
void PresetJtAccelZap(void *);
void AddSoAcceleration(SO *, QW);
extern float D_FLT_002BC990;
}
void PresetJtAccelHide(JT *);
void PresetJtAccelPipe(JT *);

struct VTENTRY { short delta; short index; QW (*pfn)(void *); };
static inline QW ScaleVector(VU_SCALE s, QW v) { return VectorScaleX(v, s.q); }
extern "C" void PresetBentleyAccel(BENTLEY *pbentley, float dt)
{
    if (pbentley->state == 0xD)
        AddSoGravityAcceleration(pbentley);
    else
        PresetStepAccel(pbentley);
    switch (pbentley->state) {
    case 2:
        bevy_player_p18_gadget_glide_force((char *)pbentley + 0x2C0);
        break;
    case 3:
        PresetJtAccelHide((JT *)((char *)pbentley + 0x4C0));
        break;
    case 4:
        PresetJtAccelZap((char *)pbentley + 0xDF0);
        break;
    case 0xD:
        PresetJtAccelPipe((JT *)((char *)pbentley + 0xF50));
        break;
    case 6:
        if (pbentley->field_0x16B0 == 2) {
            VTENTRY *pentry = &(*(VTENTRY **)((char *)pbentley + 0xC))[33];
            void *pthis = (char *)pbentley + pentry->delta;
            QW (*pfn)(void *) = pentry->pfn;
            VU_SCALE scale;
            scale.q = QuadFromFloat(-D_FLT_002BC990);
            AddSoAcceleration(pbentley, ScaleVector(scale, pfn(pthis)));
        }
        break;
    }
}
