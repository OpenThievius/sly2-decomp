#include "sly2.h"
struct SUB { u8 unknown_0x0[0x14]; int id; };
struct ITM { short pad[4]; short flag; short pad2[7]; };
struct ENT { unsigned short count; unsigned short itemCount; SUB *subs; ITM *items; u8 unknown_0xC[0x14]; int selected; u8 unknown_0x24[0xC]; };
struct OBJ { u8 unknown_0x0[0x80]; unsigned short count; unsigned short pad2; ENT *entries; };
extern "C" void FStartSpriteLabelInstance(OBJ *, int, int, int, int);

void func_00213B00(OBJ *obj, int id)
{
    if (id == -1) return;
    for (int i = 0; i < obj->count; i++) {
        ENT *ent = &obj->entries[i];
        for (int j = 0; j < ent->count; j++) {
            SUB *sub = &ent->subs[j];
            if (id != sub->id)
                continue;
            int any = 0;
            for (int k = 0; k < ent->itemCount; k++)
                if (ent->items[k].flag != -1) any = 1;
            if (any) {
                FStartSpriteLabelInstance(obj, i, j, 0, 0);
                return;
            }
            ent->selected = j;
            return;
        }
    }
}
