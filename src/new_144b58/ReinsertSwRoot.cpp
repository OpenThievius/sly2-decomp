#include "sw.h"
void RemoveSwRoot(SW *, DLE *);
void InsertDlEntryBefore(DL *, void *, DLE *);
void ReinsertSwRoot(SW *psw, DLE *proot)
{
    RemoveSwRoot(psw, proot);
    InsertDlEntryBefore(&psw->dlRoot, psw->field_0x39A4, proot);
}
