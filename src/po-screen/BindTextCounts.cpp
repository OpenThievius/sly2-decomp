#include "types.h"
extern "C" int sprintf(char *, const char *, ...);
struct TXT { u8 unknown_0x0[0x4764]; int cur; int max; };
extern TXT B_003DD490;
void BindTextCounts(char *text)
{
    sprintf(text, "%d/%d", B_003DD490.cur, B_003DD490.max);
}
