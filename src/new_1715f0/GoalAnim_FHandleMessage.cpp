#include "sly2.h"
#include "goal.h"
#include "stepguard.h"
#include "goals.h"
#include "ps2inline.h"
#include "vu0inline.h"
union VU_SCALE { QW q; VECTOR v; };
struct VT { u8 unknown_0x0[0x118]; short delta; short index; void (*fn)(char *, QW); }; /* STEPGUARD slot 35 (Slot35) */

/* The data of an animation event message (message 9): who it came from, a float argument and the event id. */
struct ANIMEVENTMSG {
    /* 0x0 */ s32 sender;   /* GoalAnim_FHandleMessage compares it with func_00209518's id of the goal's animation */
    /* 0x4 */ f32 arg;      /* event 0x15E: the time func_00204E38 takes */
    /* 0x8 */ s32 event;    /* the event id the switch tests */
};
extern "C" {
int func_00209518(ANIMREF *);
void *func_002097C8(GUARDHEADING *, GOAL *);
void func_002097D8(GUARDHEADING *, GOAL *);
void func_001EEFC0(GOAL *, int);
void func_001EF038(GOAL *, int);
int func_001A6AF8(void *, PO *);
QW func_00204E38(STEPGUARD *, int, float);
void func_001F7A68(STEPGUARD *, int);
GOAL *func_00205458(STEPGUARD *, int);
PO *PpoSwFocusBase(char *);
void TriggerJoyRumbleRumk__FP3JOY4RUMKf(void *, int, float);
void JoltCm(void *, int);
extern char B_002DDF40[];
extern char B_002DFC00[];
extern char B_003DD490[];
extern PO *g_2f7900;
#define guard GOAL_GUARD(goal)
int GoalAnim_FHandleMessage(GOALANIM *goal, int message, ANIMEVENTMSG *data) {
    if (message == 9) {
        ANIMREF *animref = goal->panimref;
        if (animref != 0) {
            int sender = func_00209518(animref);
            if (sender == data->sender) {
                switch (data->event) {
                case 0x15E: {
                    QW vel = func_00204E38(guard, sender, data->arg);
                    VU_SCALE scale;
                    scale.q = VectorFromFloat(-1.0f);
                    *(QW *)((char *)guard + 0x190) = VectorScaleX(vel, scale.q);
                    /* kept as the hand-written byte offsets: typed members (guard->velGoal, matHeading) and the virtual Slot35 hoist the guard
                       load and move the vtable and matrix loads after TransformVector (scores 36 to 76), retail loads them first */
                    char *base = (char *)guard;
                    VT *vtable = *(VT **)(base + 0xC);
                    QW *rows = (QW *)(base + 0x1B0);
                    QW row0 = rows[0];
                    QW row1 = rows[1];
                    QW row2 = rows[2];
                    char *self = base + vtable->delta;
                    void (*fn)(char *, QW) = vtable->fn;
                    QW world = TransformVector(vel, row0, row1, row2);
                    fn(self, world);
                    return 1;
                }
                case 0x25:
                    func_002097C8(&guard->heading, goal);
                    return 1;
                case 0x26:
                    func_002097D8(&guard->heading, goal);
                    return 1;
                case 0x29:
                    guard->fLock = 1;
                    return 1;
                case 0x2A:
                    guard->fLock = 0;
                    return 1;
                case 0x27:
                    func_001EEFC0(goal, sender);
                    return 1;
                case 0x28:
                    func_001EF038(goal, sender);
                    return 1;
                case 0x2F: {
                    GOALNOTICE *obj = (GOALNOTICE *)func_00205458(guard, 0xA5);
                    if (obj != 0) {
                        if ((PO *)obj->ptarget == PpoSwFocusBase(B_003DD490))
                            TriggerJoyRumbleRumk__FP3JOY4RUMKf(B_002DFC00, 8, 1.0f);
                    }
                    return 0;
                }
                case 0x34:
                case 0x35: {
                    PO *focus = PpoSwFocusBase(B_003DD490);
                    GOALHIT *obj = (GOALHIT *)func_00205458(guard, 0xA0);
                    if (obj != 0 && func_001A6AF8((void *)obj->args.arg, focus) != 0) {
                        if (focus == g_2f7900) {
                            int type = data->event;
                            if (type != 0x34) {
                                if (type == 0x35) JoltCm(B_002DDF40, 0);
                            } else {
                                TriggerJoyRumbleRumk__FP3JOY4RUMKf(B_002DFC00, 3, 0.15f);
                            }
                        }
                    }
                    return 0;
                }
                case 0x36:
                    func_001F7A68(guard, 2);
                    return 0;
                default:
                    return 0;
                }
            }
        }
    }
    return 0;
}
}
