#include "types.h"
struct UL { u64 v; } __attribute__((packed));
extern "C" {
float PostLoLoad();
void QueueSwCallback(char *, int, u64, int);
extern char B_003DD490[];
extern const UL RO_002A5010;
void PostRhythmLoad(int arg0) {
    PostLoLoad();
    QueueSwCallback(B_003DD490, arg0, RO_002A5010.v, 0);
}
}
