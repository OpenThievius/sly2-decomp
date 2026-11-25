#include "sly2.h"
#include "button.h"
extern char B_002DEB30[];
void func_00161F10(char *, u8 *, int, s32 *, int, int);
void func_00148B78(BTN *pbtn, int x, int y)
{
    func_00161F10(B_002DEB30, pbtn->ataskreq, 4, &pbtn->ctaskreq, x, y);
}
