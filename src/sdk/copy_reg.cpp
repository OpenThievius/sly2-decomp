#include "types.h"
extern "C" {
extern void *get_reg_addr(int, void *, int);
extern void *memcpy(void *, const void *, u64);
void copy_reg(int regno, void *source_context, void *destination_context) {
    void *source = get_reg_addr(regno, source_context, 0);
    void *destination = get_reg_addr(regno, destination_context, 0);
    u64 size = regno < 0x1F ? 0x10 : (regno <= 0x3F ? 4 : 8);
    memcpy(destination, source, size);
}
}
