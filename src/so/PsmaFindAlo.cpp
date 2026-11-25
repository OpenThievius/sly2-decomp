#include "sma.h"
#include "sly2.h"

extern SMA *B_003E126C;

SMA *PsmaFindAlo(void *alo, int id) {
    VECTOR local;
    SMA *sma;
    for (sma = B_003E126C; sma != 0; sma = sma->psmaNextAll) {
        if (sma->paloRoot == alo && (id == -1 || sma->psm->oid == id))
            return sma;
    }
    return 0;
}
