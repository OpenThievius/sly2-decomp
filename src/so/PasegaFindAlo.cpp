#include "asega.h"
#include "sly2.h"

extern ASEGA *B_003E1218;

ASEGA *PasegaFindAlo(void *plo, int id) {
    VECTOR local;
    ASEGA *ppasega;
    for (ppasega = B_003E1218; ppasega != 0; ppasega = ppasega->pasegaNextAll) {
        if (ppasega->paloRoot == plo && (id == -1 || ppasega->paseg->oid == id))
            return ppasega;
    }
    return 0;
}
