#include "types.h"
#include "vu0inline.h"
#include "step.h"
#include "oxa.h"
#include "guard.h"
/* a local view of the SENSOR words at 0xF0 and 0xF4 (guard.h leaves them a gap): only this function reads them */
struct SENSORFORCE { u8 unknown_0x0[0xF0]; int fForce; int fSuppress; };
struct CLIPEDGE { char data[0x180]; };
/* a STEP (class 0x33) or a JT (class 0x34, whose 0x11AC is a gap in jt.h: this function is its only reader) */
struct OBJ : STEP {
    u8 unknown_0x2C0[0x11AC - 0x2C0];
    int field11AC;
};
struct NODE { int hit; NODE *next; u8 unknown_0x8[4]; OBJ *pobj; };
struct BSP { u8 unknown_0x0[0xEC]; void *pclip; u8 unknown_0xF0[0x130 - 0xF0]; BSP *pnext; };
extern "C" {
void *PpoSwFocusBase(void *);
int FSwBinocActive(void *);
int FIsLoInWorld(OBJ *);
int FIsBasicDerivedFrom(void *, int);
QW PosLoWorld(OBJ *);
QW func_00153E60(SENSOR *);
QW ConvertAloPos(void *, BSP *, QW);
int ClsgClipEdgeToBsp(void *, int, QW, QW, int, CLIPEDGE *);
int func_00227C90(void *, QW);
int func_00154770(SENSOR *, OBJ *);
int FSensorSightBlocked(SENSOR *, OBJ *);
extern char B_003DD490;
extern BSP *B_003E1480;
}

extern "C" int NNextSensorState(SENSOR *psensor, OBJ *pobj, int state)
{
    CLIPEDGE clip;
    void *pfocus = PpoSwFocusBase(&B_003DD490);
    if (pobj == 0 || !FIsLoInWorld(pobj)) {
        state = 0;
    } else if (FIsBasicDerivedFrom(pobj, 0x32) && pobj->NAlertLevel() == 2) {
        state = 0;
    } else if (FIsBasicDerivedFrom(pobj, 0x34) && pfocus && FIsBasicDerivedFrom(pfocus, 0x46)) {
        state = 0;
    } else if (FSwBinocActive(&B_003DD490)) {
        state = 0;
    } else if (((SENSORFORCE *)psensor)->fSuppress) {
        state = 0;
    } else if (FIsBasicDerivedFrom(pobj, 0x34) && pobj->field11AC) {
        state = 0;
    } else if (((SENSORFORCE *)psensor)->fForce) {
        state = 1;
    } else {
        QW pos;
        if (FIsBasicDerivedFrom(pobj, 0x33))
            pos = VectorAdd(PosLoWorld(pobj), pobj->posLocal);
        else
            pos = PosLoWorld(pobj);
        for (BSP *pbsp = B_003E1480; pbsp; pbsp = pbsp->pnext) {
            QW from = ConvertAloPos(0, pbsp, func_00153E60(psensor));
            QW to = ConvertAloPos(0, pbsp, pos);
            if (ClsgClipEdgeToBsp(pbsp->pclip, 0x7FFFFFFF, from, to, 4, &clip) > 0) {
                state = 0;
                goto done;
            }
        }
        switch (state) {
        case 0: {
            OXA *pset = psensor->poxa;
            if (pset) {
                for (NODE *pnode = (NODE *)pset->first; pnode; pnode = pnode->next) {
                    if (pnode->pobj == pobj) {
                        if (pnode->hit) {
                            state = 1;
                            goto done;
                        }
                        break;
                    }
                }
            }
            if (!func_00227C90(psensor->pvolume, pos)) {
                state = 0;
            } else if ((void *)psensor->field_0xEC && !func_00227C90((void *)psensor->field_0xEC, pos)) {
                state = 0;
            } else if ((psensor->grfSensing & 1) || !func_00154770(psensor, pobj)) {
                state = 1;
                if (!(psensor->grfSensing & 2))
                    state = FSensorSightBlocked(psensor, pobj) == 0;
            } else {
                state = 0;
            }
            break;
        }
        case 1:
            if ((void *)psensor->field_0xEC && !func_00227C90((void *)psensor->field_0xEC, pos)) {
                state = 0;
            } else if (!func_00227C90(psensor->pvolume, pos)) {
                state = 2;
            } else if (psensor->grfSensing & 8) {
                if (FSensorSightBlocked(psensor, pobj))
                    state = 0;
            }
            break;
        case 2:
            if ((void *)psensor->field_0xEC && !func_00227C90((void *)psensor->field_0xEC, pos)) {
                state = 0;
            } else if (func_00227C90(psensor->pvolume, pos)) {
                if ((psensor->grfSensing & 2) || !FSensorSightBlocked(psensor, pobj))
                    state = 1;
            } else if (psensor->grfSensing & 8) {
                if (FSensorSightBlocked(psensor, pobj))
                    state = 0;
            }
            break;
        }
    }
done:
    return state;
}
