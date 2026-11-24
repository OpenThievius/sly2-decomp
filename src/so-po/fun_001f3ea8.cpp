#include "types.h"
#include "so.h"
#include "oxa.h"
extern "C" void func_001A6178(SO *);
extern "C" void AddAloToRenderTree(SO *);
extern "C" int FFindDlEntry(void *, void *);
extern "C" void AppendDlEntry(void *, void *);
extern "C" char B_003E11AC;
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));

void func_001F3EA8(SO *self)
{
    VECTOR vector;
    func_001A6178(self);
    if ((self->grfso & (1UL << 35)) != 0) {
        int holderValue = self->grfSw;
        int isUntagged = !(holderValue & 1);
        if (isUntagged)
            holderValue = *(int *)holderValue;
        if ((holderValue & 8) != 0)
            AddAloToRenderTree(self);
    }
    LO *node = (LO *)self->dlChild.head;
    while (node != self->ploChildEnd) {
        node->Slot23();
        node = node->ploNext;
    }
    OXA *entry = self->poxa;
    if (entry != 0 && entry->owner == self) {
        char *list = &B_003E11AC;
        if (FFindDlEntry(list, entry) == 0)
            AppendDlEntry(list, self->poxa);
        /* SO slot 49, called here without an argument (so.h declares Slot49(int) from func_0010DAF0) */
        char *typeInfo = *(char **)((char *)self + 0xC);
        ((void (*)(char *))*(void **)(typeInfo + 0x18C))((char *)self + *(short *)(typeInfo + 0x188));
    }
}
