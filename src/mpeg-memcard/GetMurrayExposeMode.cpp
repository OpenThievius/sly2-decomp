#include "sly2.h"
#include "murray.h"
extern "C" int func_001409B8();
extern "C" int GetMurrayExposeMode(MURRAY *pmurray)
{
    int mode = func_001409B8();
    if (mode == -1) {
        switch (pmurray->state) {
        case 1:
        case 12:
            return 1;
        case 9:
            return pmurray->field_0x17F4 ? 1 : mode;
        default:
            return -1;
        }
    }
    return mode;
}
