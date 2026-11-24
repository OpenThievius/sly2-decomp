#include "ps2inline.h"
#include "mpeg.h"
extern int func_00239450();
extern void func_002394A0();
extern char D_451E80[];
void func_00252608(MPEGDEC *decoder)
{
    int index;
    int count;
    int flag;
    u64 *tag;
    int slot;
    if (decoder->sameFrame == 0) {
    index = decoder->bufferIndex;
    count = decoder->buffers[index].blockCount;
    tag = (u64 *)(((uptr)D_451E80 & 0xFFFFFFF) | 0x20000000);
    for (slot = 0; slot < count; slot++) {
        unsigned first = (unsigned)decoder->buffers[index].upper[slot];
        unsigned second = (unsigned)decoder->buffers[index].lower[slot];
        u64 head = ((u64)(first & 0xFFFFFFF) << 32) | 0x30000000UL;
        u64 last = (slot == count - 1) ? 0 : 3;
        u64 tail = ((u64)(second & 0xFFFFFFF) << 32) | (last << 28);
        head |= 0x30;
        tail |= 0x30;
        tag[0] = head;
        tag[2] = tail;
        tag += 4;
    }
    flag = func_00239450();
    MemoryBarrier();
    *(volatile unsigned *)0x1000D480 = (unsigned)decoder->buffers[decoder->bufferIndex].base;
    *(volatile unsigned *)0x1000D430 = (uptr)D_451E80;
    *(volatile unsigned *)0x1000D420 = 0;
    *(volatile unsigned *)0x1000D400 = 0x105;
    if (flag) {
        func_002394A0();
        return;
    }
    }
}
