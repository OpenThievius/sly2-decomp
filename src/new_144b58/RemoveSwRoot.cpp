#include "types.h"
#include "sw.h"
extern "C" {
s32 FFindDlEntry(DL *, DLE *);
void RemoveDlEntry(DL *, DLE *);
void RemoveSwRoot(SW *psw, DLE *proot) {
    DL *pdl = &psw->dlRoot;
    if (FFindDlEntry(pdl, proot) != 0) {
        if (psw->field_0x39A4 == proot) {
            psw->field_0x39A4 = proot->prev;
        }
        RemoveDlEntry(pdl, proot);
    }
}
}
