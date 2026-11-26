#include "types.h"
#include "jt.h"
#include "joy.h"
#include "ps2inline.h"
#include "vu0inline.h"
struct XPENTRY { u8 unknown_0x0[8]; s32 kind; u8 unknown_0xC[0x34]; };
struct XPARG {
    u8 unknown_0x0[0x40];
    VECTOR velocity;
    u8 *pbEntries;
};
union VU_SCALE { QW q; VECTOR v; };
extern s32 g_2e1e40;
extern s32 g_2dd5bc;
extern s32 g_2f7900;
extern "C" {
s32 bevy_player_p4_144068(JT *);
void AdjustSoXpVelocity(JT *, s32, XPARG *, s32, s32);
}
void AdjustJtXpVelocity(JT *pjt, s32 a1, XPARG *pxp, s32 a3, s32 index)
{
    VU_SCALE scale;
    QW saved = *(QW *)&pxp->velocity;
    s32 kind = ((XPENTRY *)(pxp->pbEntries + ((1 - index) << 6)))->kind;
    if (kind == g_2e1e40 || kind == g_2dd5bc || kind == g_2f7900) {
        if (pjt->pjoy->vjoym != 1 || bevy_player_p4_144068(pjt) != 0) {
            scale.q = VectorFromFloat(0.01f);
            *(QW *)&pxp->velocity = VectorScaleX(saved, scale.q);
        }
    }
    AdjustSoXpVelocity(pjt, a1, pxp, a3, index);
    *(QW *)&pxp->velocity = saved;
}
