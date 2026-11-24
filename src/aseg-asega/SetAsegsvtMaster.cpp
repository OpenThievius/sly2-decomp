#include "types.h"
#include "asega.h"

extern "C" {
void SetAsegaMasterSpeed(ASEGA *, f32);

void SetAsegsvtMaster(ASEG *aseg, f32 svtMaster) {
    /* stack area retail keeps at 0x0..0xF with no stores */
    s8 sp[0x10] __attribute__((aligned(16)));
    ASEGA *asega;

    asega = (ASEGA *)aseg->dlAsega.head;
    if (asega != 0) {
        do {
            SetAsegaMasterSpeed(asega, svtMaster);
            asega = asega->pasegaNext;
        } while (asega != 0);
    }
    aseg->svtMaster = svtMaster;
}

}
