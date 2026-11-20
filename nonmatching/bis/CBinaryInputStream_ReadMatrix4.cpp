#include "types.h"
extern "C" {
struct VECTOR;

struct Matrix4Dest {
    char pad_0x0[0xC];
    s32 field_0xC;
    char pad_0x10[0xC];
    s32 field_0x1C;
    char pad_0x20[0xC];
    s32 field_0x2C;
    char pad_0x30[0xC];
    f32 field_0x3C;
};

void CBinaryInputStream_ReadMatrix(); /* extern */
void ReadVector__18CBinaryInputStreamP6VECTOR(s32, VECTOR *); /* extern */

void CBinaryInputStream_ReadMatrix4(s32 stream, Matrix4Dest *matrix) {
    CBinaryInputStream_ReadMatrix();
    ReadVector__18CBinaryInputStreamP6VECTOR(stream, (VECTOR *)((char *)matrix + 0x30));
    matrix->field_0xC = 0;
    matrix->field_0x1C = 0;
    matrix->field_0x2C = 0;
    matrix->field_0x3C = 1.0f;
}

}
