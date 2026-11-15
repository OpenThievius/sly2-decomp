#include "sly2.h"

struct PASEGA {
    char pad0[0x14];
    struct PASEG *paseg;
    void *plo;
    char pad1[0x8];
    struct PASEGA *ppasegaNext;
};
struct PASEG {
    char pad[0x18];
    int id;
};
extern PASEGA *B_003E1218;

PASEGA *PasegaFindAlo(void *plo, int id) {
    VECTOR local;
    PASEGA *ppasega;
    for (ppasega = B_003E1218; ppasega != 0; ppasega = ppasega->ppasegaNext) {
        if (ppasega->plo == plo && (id == -1 || ppasega->paseg->id == id))
            return ppasega;
    }
    return 0;
}
