#include "saa.h"
extern "C" {
extern SAA *B_003E159C;
SAA *PsaaFromOid(int oid)
{
    char frame[0x10] __attribute__((aligned(16)));
    if (oid == -1)
        return 0;
    SAA *psaa = B_003E159C;
    while (psaa && psaa->owner == 0) {
        if (psaa->oid == oid)
            return psaa;
        psaa = psaa->next;
    }
    return 0;
}
}
