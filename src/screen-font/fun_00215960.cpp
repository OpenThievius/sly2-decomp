#include "fbsprite.h"
extern "C" {
void PrependSlEntry(SL *, void *);
void func_002185F8(int, int, int, MOVIECHAR *);
void func_00215960(MOVIECHAR *command, SLOT *slot, int flag) {
    switch (command->type) {
    case 4:
        func_002185F8(command->pblot->asprite + command->id * 0x30, slot->iinst, slot->flag, command);
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
