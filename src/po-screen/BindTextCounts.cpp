#include "sw.h"
extern "C" int sprintf(char *, const char *, ...);
extern SW B_003DD490;
void BindTextCounts(char *text)
{
    sprintf(text, "%d/%d", B_003DD490.cclueFound, B_003DD490.cclueMax);
}
