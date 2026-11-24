#include "types.h"
#include "guardview.h"
#include "goals.h"
extern float g_2dded0;
extern float D_FLT_002BE610;
struct GOALREACTRANGE *PsenseFindNotice(struct STEPGUARDVIEW *, struct LO *, struct ALERT *);
int func_00175FF0(struct GOALNOTICE *notice) {
    struct STEPGUARDVIEW *sense = (struct STEPGUARDVIEW *)notice->pstep;
    struct GOALREACTRANGE *found = PsenseFindNotice(sense, notice->ptarget, sense->palert);
    notice->prange = found;
    if (found != 0) {
        return 1;
    }
    sense = (struct STEPGUARDVIEW *)notice->pstep;
    if (sense->tCooldown < g_2dded0) {
        sense->tCooldown = g_2dded0 + D_FLT_002BE610;
    }
    return 0;
}
