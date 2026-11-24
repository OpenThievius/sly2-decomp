#include "blot.h"
/* a queued sprite command of a blot (the first argument of func_00215960): its kind, the blot, and a sprite index */
struct BLOTCOMMAND {
    u8 unknown_0x0[0x4];
    s32 kind;
    BLOT *pblot;
    u8 unknown_0xC[0x4];
    s32 index;
};
/* a sprite slot: the label's sprite at 0x58 and its flag byte at 0x61 */
struct BLOTSLOT {
    u8 unknown_0x0[0x58];
    s32 asprite;
    u8 unknown_0x5C[0x5];
    u8 flag;
};
extern "C" {
void PrependSlEntry(SL *, void *);
void func_002185F8(int, int, int, BLOTCOMMAND *);
void func_00215960(BLOTCOMMAND *command, BLOTSLOT *slot, int flag) {
    switch (command->kind) {
    case 4:
        func_002185F8(command->pblot->asprite + command->index * 0x30, slot->asprite, slot->flag, command);
        return;
    case 1:
    case 3:
    case 6:
    case 7:
        slot->flag = flag;
        PrependSlEntry(&command->pblot->sl, slot);
    default:
        return;
    }
}
}
