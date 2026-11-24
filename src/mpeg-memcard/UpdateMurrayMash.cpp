#include "murray.h"
extern "C" char B_003DD490[];
extern "C" int D_002C0908[][5];
extern "C" int D_002C0948[][5];
extern "C" const float RO_002C0900;
extern "C" float g_2dded4;

extern "C" int PpoSwFocusBase(void *);
extern "C" int FSwHandsOff(void *);
extern "C" int GetSmaCur(int);
extern "C" int GetSmaGoal(int);
extern "C" int FButtonPressedWithin(int, int, float);
extern "C" void SetSmaGoal__FP3SMA3OID(int, int);

void UpdateMurrayMash(MURRAY *arg0)
{
    float temp_f2;
    int temp_a0_2;
    int var_s1;

    if (PpoSwFocusBase(B_003DD490) == (sptr)arg0 && FSwHandsOff(B_003DD490) == 0) {
        var_s1 = GetSmaCur((int)arg0->field_0x1034);
        if (var_s1 == GetSmaGoal((int)arg0->field_0x1034) && var_s1 < 0x1D0 && var_s1 >= 0x1CB) {
            arg0->tMashLeft = arg0->tMashLeft - g_2dded4;
            if (FButtonPressedWithin((int)arg0->pjoy, 0xF0, 0.0f) != 0) {
                arg0->cMashLeft = arg0->cMashLeft - 1;
                arg0->field_0x1528 = arg0->tMashLeft;
            }
            temp_f2 = arg0->tMashLeft;
            if (temp_f2 <= 0.0f) {
                if (arg0->cMashLeft <= 0)
                    var_s1 = D_002C0908[arg0->iMashLevel][var_s1 - 0x1CB];
                else
                    var_s1 = D_002C0948[arg0->iMashLevel][var_s1 - 0x1CB];
            } else if (RO_002C0900 < arg0->field_0x1528 - temp_f2) {
                var_s1 = 0x1CA;
            }
            temp_a0_2 = (int)arg0->psmaPartner;
            if (temp_a0_2 != 0)
                SetSmaGoal__FP3SMA3OID(temp_a0_2, var_s1);
            SetSmaGoal__FP3SMA3OID((int)arg0->field_0x1034, var_s1);
        }
    }
}
