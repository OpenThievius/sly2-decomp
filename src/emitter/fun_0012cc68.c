/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

/* the object whose vtable is D_002CA8A0 (src/data/ac.cpp); this function is its slot 3 and reads the float from a stream */
struct AC {
    u8 unknown_0x0[4];
    f32 field_0x4;
};

f32 F32Read__18CBinaryInputStream(void *stream);

void func_0012CC68(struct AC *object, void *stream) {
    object->field_0x4 = F32Read__18CBinaryInputStream(stream);
}
