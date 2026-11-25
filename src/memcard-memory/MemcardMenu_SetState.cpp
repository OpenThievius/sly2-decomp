#include "types.h"
struct O;
struct VT_1ACB58 {
    u8 unknown_0x0[0x50]; short delta50; short pad52; void (*fn54)(void *);
    u8 unknown_0x58[0x188 - 0x58]; short delta188; short pad18A; void (*fn18C)(void *, int);
};
struct O {
    u8 unknown_0x0[0xC]; VT_1ACB58 *vt; u8 unknown_0x10[0x14]; O *child; u8 unknown_0x28[0x18]; int state;
};
extern "C" {
void MemcardMenu_SetState(O *self, int state) {
    self->state = state;
    if (self->child) {
        self->vt->fn54((char *)self + self->vt->delta50);
        O *child = self->child;
        child->vt->fn18C((char *)child + child->vt->delta188, -1);
    }
}
}
