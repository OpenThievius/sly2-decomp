#include "types.h"
typedef struct Slot { struct Slot *next; volatile int id; int (*field8)(int, int, int, int); int fieldC; } Slot;  // volatile-ok: id is written by this alarm callback (interrupt context) and by the callers between interrupt disable and enable
extern Slot *B_0044E700;
static inline void SlotPush(Slot *entry) {
    entry->next = B_0044E700;
    B_0044E700 = entry;
    entry->id = 0;
}
int func_0023A668(int id, int arg1, int arg2, Slot *slot) {
    int result = slot->field8(((sptr)slot << 4) | (id & 0xFE) | 1, arg1, arg2, slot->fieldC);
    if (result == 0) {
        SlotPush(slot);
        return -1;
    }
    return result;
}
