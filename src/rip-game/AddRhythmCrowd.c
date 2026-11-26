#include "types.h"

/* a C view of rhythm.h's RHYTHMCROWD and RHYTHM (C++ only): the names are the shared header's */
struct RHYTHMCROWD {
    s32 oid;
    s32 oidCheer;
    void *link;
    s32 level;
    f32 threshold[3];
};

struct RHYTHM {
    u8 unknown_0x0[0x2A8];
    u32 ccrowd;
    struct RHYTHMCROWD acrowd[0x80];
};

void AddRhythmCrowd(struct RHYTHM *prhythm, s32 oid, s32 oidCheer) {
    u32 temp_a0;
    struct RHYTHMCROWD *pcrowd;

    temp_a0 = prhythm->ccrowd;
    if (temp_a0 < 0x80U) {
        prhythm->ccrowd = (u32) (temp_a0 + 1);
        pcrowd = &prhythm->acrowd[temp_a0];
        pcrowd->oid = oid;
        pcrowd->oidCheer = oidCheer;
        pcrowd->level = -1;
    }
}
