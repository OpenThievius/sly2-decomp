#include "types.h"

s32 func_00235B08(void *, void *, s32, s32, void *);
s32 func_00236820(void);

struct PRINTCONTEXT { s32 target; };

s32 func_00236918(s32 arg0, s32 arg1, s32 arg2, ...)
{
    struct PRINTCONTEXT context;
    void *args;

    context.target = arg0;
    args = (char *)__builtin_next_arg(arg2) - 0x28;
    return func_00235B08(func_00236820, &context, arg1, arg2, args);
}
