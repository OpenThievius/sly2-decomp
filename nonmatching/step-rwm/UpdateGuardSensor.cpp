#include "types.h"
#include "ps2inline.h"
#include "vu0inline.h"

struct SENSEDCAND { float dist; int *group; char *other; int sensed; float time; int pad14; };
struct SENSORENTRY { char *object; int sensed; float time; int padC; };
struct GUARDSENSOR { char pad[0xFC]; int count; SENSORENTRY entries[1]; };
struct GUARDTARGET { char pad[0xC]; char *object; };
struct SENSORGUARD {
    char pad0[0x2C0]; u64 grfsgs; char pad2C8[0x394 - 0x2C8];
    int cgroup; int agroup[3]; int csensed; char pad3A8[0x3CC - 0x3A8];
    GUARDTARGET *ptarget; char pad3D0[0xF64 - 0x3D0];
    GUARDSENSOR *psensor;
};
extern "C" {
int AddGuardSensedObject(SENSORGUARD *, char *, int *);
int CploFindSwObjectsByClass(void *, int, int, void *, int, char **);
u64 GrfsgsFromSgs(int);
SENSORENTRY *PentryFindSensorLo(GUARDSENSOR *, char *);
QW PosLoWorld(void *);
int SetAlertState(GUARDTARGET *, int);
void func_00153DE0(GUARDSENSOR *);
void qsort(void *, int, int, int (*)(const void *, const void *));
int func_002068D8(const void *, const void *);
extern u64 B_003DD480;
extern int B_003DD488;
extern char B_003DD490;
extern float D_FLT_002C3D04;
extern float D_FLT_002C3D08;
extern float D_FLT_002C3D0C;
}

extern "C" void UpdateGuardSensor(SENSORGUARD *guard)
{
    SENSEDCAND acand[0x40];
    char *aplo[0x100];
    if (B_003DD488 == 0) {
        u64 a = GrfsgsFromSgs(5);
        u64 b = GrfsgsFromSgs(6);
        u64 c = GrfsgsFromSgs(0x17);
        u64 d = GrfsgsFromSgs(7);
        u64 e = GrfsgsFromSgs(0x10);
        u64 f = GrfsgsFromSgs(1);
        u64 g = GrfsgsFromSgs(0x16);
        u64 h = GrfsgsFromSgs(0x2A);
        B_003DD488 = 1;
        B_003DD480 = a | b | c | d | e | f | g | h;
    }
    if (guard->grfsgs & B_003DD480)
        return;
    if (guard->cgroup != 0) {
        int count = 0;
        for (int igroup = 0; igroup < guard->cgroup; igroup++) {
            int *group = &guard->agroup[igroup];
            int cplo = CploFindSwObjectsByClass(&B_003DD490, 0x505, *group, 0, 0x100, aplo);
            for (int iplo = 0; iplo < cplo; iplo++) {
                char *other = aplo[iplo];
                if (other == (char *)guard)
                    continue;
                QW posSelf = PosLoWorld(guard);
                QW posOther = PosLoWorld(other);
                float distance = LaneX(SqrtX(SquaredLengthXy(VectorSub(posSelf, posOther))));
                if (distance < D_FLT_002C3D04 && (unsigned)count < 0x40) {
                    SENSEDCAND *cand = &acand[count];
                    GUARDSENSOR *sensor = guard->psensor;
                    cand->dist = distance;
                    cand->sensed = -1;
                    cand->group = group;
                    cand->other = other;
                    cand->time = -3.4028235e38f;
                    count++;
                    for (int ientry = sensor->count - guard->csensed; ientry < guard->psensor->count; ientry++) {
                        SENSORENTRY *entry = &guard->psensor->entries[ientry];
                        if (entry->object == cand->other) {
                            cand->sensed = entry->sensed;
                            cand->time = entry->time;
                            break;
                        }
                    }
                }
            }
        }
        qsort(acand, count, sizeof(SENSEDCAND), func_002068D8);
        guard->psensor->count -= guard->csensed;
        guard->csensed = 0;
        if (count > 0) {
            SENSEDCAND *cand = acand;
            do {
                if (AddGuardSensedObject(guard, cand->other, cand->group) != 0) {
                    int sensed = cand->sensed;
                    guard->csensed++;
                    if (sensed != -1) {
                        SENSORENTRY *last = &guard->psensor->entries[guard->psensor->count - 1];
                        last->sensed = sensed;
                        last->time = cand->time;
                    }
                }
                count--;
                cand++;
            } while (count != 0);
        }
    }
    func_00153DE0(guard->psensor);
    if (guard->ptarget == 0)
        return;
    SENSORENTRY *hit = PentryFindSensorLo(guard->psensor, guard->ptarget->object);
    if (hit == 0)
        return;
    switch (hit->sensed) {
    case 1:
        SetAlertState(guard->ptarget, 1);
        break;
    case 2: {
        QW posTarget = PosLoWorld(guard->ptarget->object);
        QW posSelf = PosLoWorld(guard);
        int near = 0;
        QW delta = VectorSub(posTarget, posSelf);
        float distance = LaneX(SqrtX(SquaredLengthXy(delta)));
        if (distance < D_FLT_002C3D08) {
            if (__builtin_fabsf(LaneZInGeneralRegister(delta)) < D_FLT_002C3D0C)
                near = 1;
        }
        if (near != 0)
            SetAlertState(guard->ptarget, 2);
        break;
    }
    }
}
// lead: scored with -fno-strength-reduce row
