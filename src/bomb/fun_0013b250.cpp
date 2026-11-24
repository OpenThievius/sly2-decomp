#include "sly2.h"
#include "so.h"
/* the object a bomb is stuck to (named from this function's parameter) */
struct STICK { u8 unknown_0x0[0x18]; s32 field_0x18; };
struct BOMB : SO { /* 0x150 */ u8 unknown_0x150[0x98]; /* 0x1E8 */ STICK *pstick; };
extern QW g_2a2dd0;
extern "C" void func_001A58D0(void *, void *, int);
extern "C" void func_001F4898(void *, QW);
extern "C" void func_001F4930(void *, QW);
extern "C" void SetSoCnstrForce(void *, int);
extern "C" void SetSoCnstrTorque(void *, int);
void func_0013B250(BOMB *b, STICK *stick)
{
    b->pstick = stick;
    func_001A58D0(b, stick->field_0x18 == 1 ? 0 : stick, 3);
    func_001F4898(b, g_2a2dd0);
    func_001F4930(b, g_2a2dd0);
    SetSoCnstrForce(b, 1);
    SetSoCnstrTorque(b, 1);
    b->HandleSpliceEvent(0x1B, 0, 0, 0, 0);
}
