#include "sly2.h"
struct PDESC { u8 unknown_0x0[0x40]; };
extern PDESC* B_003E1C40;
PDESC* PdescFromLevelRow(int row)
{
    if (row == -1) return 0;
    return B_003E1C40 + row;
}
