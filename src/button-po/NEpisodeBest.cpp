#include "types.h"
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define NULL 0
#include "cref.h"
extern "C" {
CRef func_001D8A38(M2C_UNK *, M2C_UNK);
extern M2C_UNK RO_002A8A78;
s32 NEpisodeBest(void) {
    return func_001D8A38(&RO_002A8A78, 0).m_tag.m_n;
}
}
