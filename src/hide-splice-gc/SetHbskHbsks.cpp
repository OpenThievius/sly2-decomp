#include "types.h"
#include "sly2.h"
#include "ps2inline.h"
#include "vu0inline.h"
#include "so.h"
#include "xf.h"
#include "hbsk.h"

struct ROWS3 { VECTOR row[3]; };
struct NODE { u8 unknown_0x0[0x70]; QW pos; };
struct TARGET : LO { u8 unknown_0x50[0x60 - 0x50]; NODE *pnode60; u8 unknown_0x64[0x10BC - 0x64]; NODE *pnode10BC; };

extern "C" {
void func_001A58D0(HBSK *, int, int);
void SetXfKind(HBSK *, XF *, int);
void SetSoCnstrForce(HBSK *, int);
void SetSoCnstrTorque(HBSK *, int);
void func_001F68A8(HBSK *, int);
void func_00147F40(void *);
void *PmatLoWorld(HBSK *);
void TiltMatUpright__FP7MATRIX3N20(void *, void *, ROWS3 *);
ROWS3 ConvertXfMat(int, XF *, ROWS3 *);
QW DecomposeRotateMatrixEuler(ROWS3 *);
QW ConvertXfPos(int, XF *, QW);
extern char B_003DD490;
extern QW g_2a2dd0;
extern QW g_2be8f0;
}

void SetHbskHbsks(HBSK *phbsk, int hbsks)
{
    ROWS3 matrix;
    int hbsksOld = phbsk->hbsks;
    if (hbsksOld != hbsks) {
        if (hbsksOld == 2) {
            if (phbsk->fLocked != 0) {
                func_001A58D0(phbsk, 0, 0xF);
                SetXfKind(phbsk, phbsk->pxfLinear, 1);
                phbsk->pxfLinear->sub = 0;
                SetXfKind(phbsk, phbsk->pxfAngular, 1);
                phbsk->pxfAngular->sub = 0;
                phbsk->Slot35(g_2a2dd0);
                SetSoCnstrForce(phbsk, 0);
                SetSoCnstrTorque(phbsk, 0);
                func_001F68A8(phbsk, 0);
            }
            phbsk->HandleSpliceEvent(6, 0, 0, 0, 0);
            func_00147F40(&B_003DD490);
            phbsk->pjt = 0;
        }
        if (hbsks == 2) {
            if (phbsk->fLocked != 0) {
                SetSoCnstrForce(phbsk, 1);
                SetSoCnstrTorque(phbsk, 1);
                TARGET *ptarget = (TARGET *)phbsk->pjt;
                NODE *pnode = ptarget->pnode10BC;
                if (pnode == 0)
                    pnode = ptarget->pnode60;
                phbsk->SetParent(ptarget, pnode, 3);
                TiltMatUpright__FP7MATRIX3N20(PmatLoWorld(phbsk), 0, &matrix);
                matrix = ConvertXfMat(0, phbsk->pxfAngular->pxfParent, &matrix);
                QW euler = DecomposeRotateMatrixEuler(&matrix);
                SetXfKind(phbsk, phbsk->pxfAngular, 7);
                VECTOR *pvec = (VECTOR *)&phbsk->pxfAngular->posGoal;
                pvec->x = 0.0f;
                pvec->z = LaneZInGeneralRegister(euler);
                pvec->y = 0.0f;
                phbsk->pxfAngular->sub = hbsks;
                QW position = ConvertXfPos(0, phbsk->pxfLinear->pxfParent, VectorAdd(pnode->pos, g_2be8f0));
                SetXfKind(phbsk, phbsk->pxfLinear, 7);
                phbsk->pxfLinear->posGoal = position;
                phbsk->pxfLinear->sub = hbsks;
                func_001F68A8(phbsk, 1);
            }
            phbsk->HandleSpliceEvent(5, 0, 0, 0, 0);
            phbsk->hbsks = hbsks;
        } else {
            phbsk->hbsks = hbsks;
        }
        phbsk->uFade = g_2dded0.t;
    }
}
