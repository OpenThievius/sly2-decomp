#include "so.h"
extern "C" {
/* the targets' view as in ShowReconLinks: SO word 0x100 is an LO (one reader on a guessed class) */
struct SORECON { u8 unknown_0x0[0x100]; LO *plo; };
struct RECON { u8 unknown_0x0[0x30]; s32 ctarget; SO *aptarget[16]; u8 unknown_0x74[0x44]; s32 field_0xB8; }; /* field_0xB8: reader bevy_ui_binoc_recon_2022d8 only */
s32 bevy_ui_binoc_recon_2022d8(RECON *arg0) {
    if (arg0->field_0xB8 != 0)
        return 1;
    for (s32 i = 0; i < arg0->ctarget; i++) {
        SO *p = arg0->aptarget[i];
        if ((s32)(p->grfo >> 60) & 1) {
            LO *q = ((SORECON *)p)->plo;
            if (q == 0)
                return 1;
            if ((s32)(q->grfo >> 60) & 1) {
            } else {
                return 1;
            }
        }
    }
    return 0;
}
}
