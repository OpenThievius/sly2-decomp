#include "sly2.h"

struct SMA_ID_HOLDER {
    char pad0[0x18];
    int id;
};
struct SMA {
    char pad0[0x1C];
    SMA *next;
    char pad1[0x4];
    SMA_ID_HOLDER *holder;
    void *alo;
};
extern SMA *B_003E126C;

SMA *PsmaFindAlo(void *alo, int id) {
    VECTOR local;
    SMA *sma;
    for (sma = B_003E126C; sma != 0; sma = sma->next) {
        if (sma->alo == alo && (id == -1 || sma->holder->id == id))
            return sma;
    }
    return 0;
}
