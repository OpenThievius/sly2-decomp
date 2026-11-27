#include "types.h"
#include "jt.h"
#include "joy.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "xp.h"
struct XPARG {
    u8 unknown_0x0[0x40];
    VECTOR velocity;
    XP *pxp;          /* the contact the velocity is adjusted for: the other side's root object is tested */
};
union VU_SCALE { QW q; VECTOR v; };
extern SO *g_2e1e40;
extern SO *g_2dd5bc;
extern SO *g_2f7900;
extern "C" {
s32 bevy_player_p4_144068(JT *);
void AdjustSoXpVelocity(JT *, s32, XPARG *, s32, s32);
}
void AdjustJtXpVelocity(JT *pjt, s32 a1, XPARG *pxp, s32 a3, s32 index)
{
    VU_SCALE scale;
    QW saved = *(QW *)&pxp->velocity;
    SO *psoOther = pxp->pxp->axpd[1 - index].psoRoot;
    if (psoOther == g_2e1e40 || psoOther == g_2dd5bc || psoOther == g_2f7900) {
        if (pjt->pjoy->vjoym != 1 || bevy_player_p4_144068(pjt) != 0) {
            scale.q = VectorFromFloat(0.01f);
            *(QW *)&pxp->velocity = VectorScaleX(saved, scale.q);
        }
    }
    AdjustSoXpVelocity(pjt, a1, pxp, a3, index);
    *(QW *)&pxp->velocity = saved;
}
