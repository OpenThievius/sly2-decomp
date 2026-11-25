#include "types.h"
extern "C" {
struct MathError {
    u8 unknown_0x0[8];
    s64 argument;
};
double dpcmp(s64, s64);
int matherr(MathError *error) {
    dpcmp(error->argument, error->argument);
    return 0;
}
}
