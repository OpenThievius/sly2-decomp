#include "m2c_macros.h"

void *__7GLOBSET(s32);                               /* extern: GLOBSET::GLOBSET, returns its argument */
void *__builtin_new(M2C_UNK);                       /* extern */
extern M2C_UNK D_002D7A40;
extern M2C_UNK D_002D9978;

void *func_00112790(void) {
    void *temp_v0;

    temp_v0 = __builtin_new(0x170);
    M2C_FIELD(temp_v0, M2C_UNK **, 0xC) = &D_002D9978;
    M2C_FIELD(temp_v0, s32 *, 0) = 0;
    M2C_FIELD(temp_v0, s32 *, 4) = 0;
    __7GLOBSET(temp_v0 + 0x80);
    M2C_FIELD(temp_v0, M2C_UNK **, 0xC) = &D_002D7A40;
    return temp_v0;
}
