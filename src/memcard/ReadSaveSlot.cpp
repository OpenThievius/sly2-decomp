#include "sly2.h"
#include "memcard.h"
extern "C" void BuildSlotFilePath(SAVE *, SLOT *, char *);
extern "C" int FindMemcardFile(SAVE *, char *, void *);
int ReadMemcardFile(SAVE *, char *, void *, int);
int ReadSaveSlot(SAVE *psave, SLOT *pslot)
{
    char achzPath[0x50];
    int nError;
    memset(pslot, 0, sizeof(SLOT));
    BuildSlotFilePath(psave, pslot, achzPath);
    nError = FindMemcardFile(psave, achzPath, &pslot->info);
    if (nError != 0)
        return nError;
    if ((pslot->info.flags & 0xD4) != 4)
        return 0x14;
    if (pslot->info.size != 0x5408)
        return 0x1C;
    return ReadMemcardFile(psave, achzPath, pslot, sizeof(SAVEDATA));
}
