#include "types.h"
struct Option_13F810 { int pad0; unsigned int flags; u8 unknown_0x8[0x20]; };
extern "C" {
void LoadOptionFromBrx(void *, Option_13F810 *, unsigned int, void *);
int S16Read__18CBinaryInputStream(void *);
extern Option_13F810 D_002AC880[];
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(void *self, void *stream) {
    int index;
    while ((index = S16Read__18CBinaryInputStream(stream)) >= 0) {
        Option_13F810 *option = &D_002AC880[index];
        LoadOptionFromBrx(self, option, option->flags & 0x2580, stream);
    }
}
}
