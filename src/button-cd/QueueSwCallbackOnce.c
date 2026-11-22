/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "swview.h"

/* The switch message key: an 8-byte struct of halfwords, passed by value in one 64-bit register. */
typedef struct SwKey {
    short kind;
    short id;
    union {
        struct {
            short sub;
            short extra;
        } part;
        int whole;
    } detail;
} SwKey;

/* Queued callback entry (QueueSwCallback fills it: fn at 0, key at 4, arg at 0xC; next link at 0x10). */
struct CB {
    int fn;
    SwKey key;
    int arg;
    struct CB *next;
};

void QueueSwCallback(struct SWVIEW *psw, int fn, SwKey key, int arg);

/*
 * Retail spills the key register to its stack home (sd $a2,0($sp)), reads key.id and key.detail.part.sub as halfwords and
 * key.detail.whole as a word from that home, and before the call reloads the key with `ld $a2,0($sp)` in front of
 * `jal QueueSwCallback` with a nop in the delay slot. Passing the key as a `long` lets reorg move that ld into the delay
 * slot (score 4); passing it as the 8-byte struct it is (a BLKmode argument, loaded by move_block_to_reg) keeps the load
 * out of the slot, as retail has it. C, not C++: in C++ the by-value struct argument is first copied to a temporary.
 */
void QueueSwCallbackOnce(struct SWVIEW *psw, int fn, SwKey key, int arg)
{
    struct CB *callback;

    for (callback = psw->pcbFirst; callback != 0; callback = callback->next) {
        if (callback->fn == fn && callback->key.id == key.id) {
            if ((callback->key.id != -1 && callback->key.detail.part.sub == key.detail.part.sub)
                    || callback->key.detail.whole == key.detail.whole) {
                if (callback->arg == arg) {
                    return;
                }
            }
        }
    }
    QueueSwCallback(psw, fn, key, arg);
}
