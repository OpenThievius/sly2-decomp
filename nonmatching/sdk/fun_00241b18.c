typedef int s32;
s32 DeleteSema(s32);
s32 SignalSema(s32);
s32 func_00239450();
void func_002394A0();
void func_0023AE20(s32);
extern s32 D_002C6754;
extern s32 D_002C6760[];
extern s32 D_002C6768;
extern s32 D_002C676C;
extern s32 D_002C6770;
extern s32 D_002C67A0;
void func_00241B18(void) {
    s32 result;
    if (D_002C6754 != 0) {
        D_002C67A0 = -1;
        SignalSema(D_002C6760[0]);
    }
    DeleteSema(D_002C6768);
    DeleteSema(D_002C676C);
    DeleteSema(D_002C6770);
    DeleteSema(D_002C6760[0]);
    result = func_00239450();
    func_0023AE20(0x80000012);
    if (result != 0) {
        func_002394A0();
    }
}
