#include "sly2.h"
#include "ps2inline.h"
struct ACT;
struct XF;
struct Frame_226370 { QW dead[1]; };
struct TANK { char pad0[0x5C]; XF *pxf; char pad1[0x18C - 0x60]; float pan; float tilt; char pad2[0x1CC - 0x194]; int fRotAct; char pad3[8]; ACT *pact; };
extern "C" ACT *func_0012DC18(TANK *, XF *, int, int, int, QW);
extern "C" float func_0012E460(ACT **);

void func_00226370(TANK *ptank, int fRotAct)
{
    Frame_226370 frame;
    if (ptank->fRotAct == fRotAct)
        return;
    ptank->fRotAct = fRotAct;
    if (fRotAct) {
        QW euler = VectorFromFloats3(0.0f, -ptank->tilt, ptank->pan);
        frame.dead[0] = euler;
        ptank->pact = func_0012DC18(ptank, ptank->pxf, 1, 5, 3, euler);
    } else {
        func_0012E460(&ptank->pact);
    }
}
