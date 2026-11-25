#include "types.h"
typedef struct Unit {
    u8 unknown_0x0[0x14C];
    int field14C;
    u8 unknown_0x150[0x34];
    int field184;
    int field188;
    u8 unknown_0x18C[8];
    int field194;
    int pad198;
    int first[3];
    int second[3];
} Unit;
extern int func_00252148(Unit *unit, int bitCount);
void func_002547A0(Unit *unit) {
    int count;
    int index;
    if (unit->field14C != 0) {
        if (unit->field194 == 0) {
            count = 1;
        } else {
            count = unit->field188 != 0 ? 3 : 2;
        }
    } else if (unit->field184 != 3) {
        count = 1;
    } else {
        count = unit->field194 != 0 ? unit->field184 : 2;
    }
    for (index = 0; index < count; index++) {
        unit->first[index] = func_00252148(unit, 16);
        func_00252148(unit, 1);
        unit->second[index] = func_00252148(unit, 16);
        func_00252148(unit, 1);
    }
}
