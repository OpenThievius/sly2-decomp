#include "sly2.h"
#include "so.h"
/* the same view of a recon target as ShowReconLinks: SO word 0x100 is an LO (slot 9 called here), one reader on a guessed class */
struct SORECON {
    u8 unknown_0x0[0x100];
    /* 0x100 */ LO *plo;
};
struct RECON { u8 unknown_0x0[0x30]; int ctarget; SO *aptarget[1]; };
extern "C" void HideReconLinks(RECON *rec) {
    for (int index = 0; index < rec->ctarget; index++) {
        LO *link = ((SORECON *)rec->aptarget[index])->plo;
        if (link != 0) {
            link->Remove();
        }
    }
}
