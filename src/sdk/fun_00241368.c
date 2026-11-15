#include "types.h"

void func_00236960(const char *);
void func_00241830(volatile u32 *);  // volatile-ok: DMA channel register block (the caller's channel), polled by func_00241368 and by this callee

void func_00241368(volatile u32 *channel)  // volatile-ok: DMA channel register block, polled while the channel is busy
{
    s32 remaining = 0x1000000;
    u32 busy;

    busy = *channel & 0x100;
    if (busy) {
        do {
            remaining--;
            if (remaining < 0) {
                func_00236960("libdma: sync timeout\n");
                func_00241830(channel);
            }
            busy = *channel & 0x100;
        } while (busy);
    }
}
