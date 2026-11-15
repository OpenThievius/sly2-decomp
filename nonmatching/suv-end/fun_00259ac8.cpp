#include "sly2.h"

struct REGBLOCK {
    char pad0[0x28];
    unsigned long status;
    char pad1[0x10];
    volatile unsigned int command; // volatile-ok: command register of a block retail writes three times with a nop between each store (unverified which block)
};

unsigned long func_00259AC8(REGBLOCK *block) {
    unsigned long value;
    block->command = value;
    block->command = value;
    block->command = value;
    return (block->status >> 60) & 1;
}
