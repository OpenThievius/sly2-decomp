#include "sly2.h"
#include "ps2inline.h"
#include "mount.h"
#include "amb.h"
struct SMP;
/* The controller a mount reads (PO::pjoy): JOY's stick, and two words past it only Mount_Update reads (one reader: a local view). */
struct MOUNTJOY {
    u8 unknown_0x0[0x18];
    /* 0x18 */ f32 radStick;
    /* 0x1C */ f32 uStick;
    u8 unknown_0x20[0x8];
    /* 0x28 */ f32 field_0x28;   /* Mount_Update: the z of the vector it hands to func_0012D108 */
    /* 0x2C */ f32 field_0x2C;   /* Mount_Update: above 0 picks SM goal 0x68, else 0x66 */
};
extern "C" {
void ContinueAmb(AMB *);
float GSmooth__FfffP3SMPPf(float, float, float, SMP *, float *);
void Mount_SetState(MOUNT *, int);
void PauseAmb(AMB *);
void SetAmbVolume(AMB *, float);
void SetSmaGoal__FP3SMA3OID(void *, int);
QW SetVectorCylind__FP6VECTORfff(float, float, float);
void UpdateSo(MOUNT *);
void func_0012D108(void *, QW);
int func_0017F550(MOUNT *);
extern SMP D_002BE7F0;
extern float g_2be7e8;
extern float g_2dded4;
void Mount_Update(MOUNT *mount) {
    unsigned state;
    unsigned after;
    UpdateSo(mount);
    do {
        state = mount->state;
        if (state == 2 && func_0017F550(mount) != 0) {
            Mount_SetState(mount, 1);
        }
        after = mount->state;
    } while (after != state);
    switch (after) {
    case 0:
        {
            int *vec = (int *)&mount->vecStick;
            vec[2] = 0;
            vec[1] = 0;
            vec[0] = 0;
        }
        break;
    case 2:
        {
            int *vec = (int *)&mount->vecStick;
            vec[2] = 0;
            vec[1] = 0;
            vec[0] = 0;
        }
        break;
    case 3:
        {
            int *vec = (int *)&mount->vecStick;
            vec[2] = 0;
            vec[1] = 0;
            vec[0] = 0;
        }
        break;
    case 4:
        {
            int *vec = (int *)&mount->vecStick;
            vec[2] = 0;
            vec[1] = 0;
            vec[0] = 0;
        }
        break;
    case 1: {
        MOUNTJOY *data = (MOUNTJOY *)mount->pjoy;
        float scale = g_2be7e8;
        int index = 0;
        mount->radStick = data->radStick;
        mount->vecStick = SetVectorCylind__FP6VECTORfff(data->radStick, data->uStick * scale, 0.0f);
        float second = ((MOUNTJOY *)mount->pjoy)->field_0x28;
        union VectorQuad { QW q; VECTOR v; } stored;
        stored.q = VectorFromFloats3(0.0f, 0.0f, second);
        QW vector = stored.q;
        if (mount->crec > 0) {
            MOUNTREC *entry = &mount->arec[0];
            do {
                void *link = entry->pact;
                if (link != 0) {
                    func_0012D108(link, vector);
                }
                void *sma = entry->psma;
                if (sma != 0) {
                    if (((MOUNTJOY *)mount->pjoy)->field_0x2C > 0.0f) {
                        SetSmaGoal__FP3SMA3OID(sma, 0x68);
                    } else {
                        SetSmaGoal__FP3SMA3OID(sma, 0x66);
                    }
                }
                index += 1;
                entry += 1;
            } while (index < mount->crec);
        }
        break;
    }
    }
    if (mount->pamb != 0) {
        float goal;
        if (mount->state == 1) {
            goal = ((MOUNTJOY *)mount->pjoy)->uStick;
        } else {
            goal = 0.0f;
        }
        float smoothed = GSmooth__FfffP3SMPPf(mount->volAmb, goal, g_2dded4, &D_002BE7F0, 0);
        mount->volAmb = smoothed;
        SetAmbVolume(mount->pamb, smoothed);
        AMB *amb = mount->pamb;
        if (mount->volAmb > 0.0f) {
            if (amb->cPause > 0) {
                ContinueAmb(amb);
            }
        } else if (amb->cPause <= 0) {
            PauseAmb(amb);
        }
    }
}
}
