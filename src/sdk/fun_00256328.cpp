#include "types.h"
extern "C" {
struct Inner { u8 unknown_0x0[0x18]; int field18; };
struct Outer { u8 unknown_0x0[0x20]; int field20; Inner *inner; };
void func_001F4BF8(int);
void func_00256328(Outer *outer, int value) {
    outer->inner->field18 = value;
    func_001F4BF8(outer->field20);
}
}
