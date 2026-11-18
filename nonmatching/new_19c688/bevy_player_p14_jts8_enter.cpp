typedef int s32; typedef signed char s8; typedef short s16;
extern "C" {
void StartAttach(void *, s32, void *, void *);
void SetBentleyState(s32, s32, void *);
void SetJmpBodyState(void *, s32, s32);
void SetJtState(void *, s32, s32);
extern s32 g_2dd5bc;
}
static inline char *Adjust(char *base, int offset) { return base ? base + offset : 0; }
static inline void Attach(char *self, s32 flag, int offset)
{
    char *target = *(char **)(self + 0xC);
    StartAttach(*(char **)self + 0x4C0, flag, target, target ? target + offset : 0);
}
struct VT { char pad[8]; short delta; short index; void (*fn)(void *, int); };
void bevy_player_p14_jts8_enter(char *self)
{
    char *owner;
    char *target;
    switch (*(s32 *)(self + 0x1C)) {
    case 6:
        Attach(self, 1, 0x150);
        return;
    case 11:
        Attach(self, 0, 0x190);
        return;
    case 12:
        Attach(self, 0, 0xE0);
        return;
    case 13:
        target = *(char **)(self + 0xC);
        StartAttach(*(char **)self + 0x4C0, *(s32 *)(target + 0x10C), target, target ? target + 0xE0 : 0);
        return;
    case 9:
        Attach(self, 4, 0xE0);
        return;
    case 10:
        Attach(self, 3, 0x190);
        return;
    case 14:
        target = *(char **)(self + 0xC);
        self = *(char **)self;
        *(char **)(self + 0x18C4) = target;
        if (*(s32 *)(target + 0x124) == 3) {
            SetJtState(self, 0x16, -1);
            return;
        }
        SetJtState(self, 3, 1);
        return;
    case 15: {
        *(char **)(*(char **)self + 0xF5C) = *(char **)(self + 0xC);
        *(float *)(*(char **)self + 0xF60) = *(float *)(self + 0x14);
        self = *(char **)self;
        char *obj = *(char **)(self + 0xC);
        (*(void (**)(void *, int))(obj + 0x2C4))(self + *(s16 *)(obj + 0x2C0), 8);
        return;
    }
    case 16:
        owner = *(char **)self;
        *(char **)(owner + 0x1F18) = *(char **)(self + 0xC);
        SetJtState(owner, 0x15, 10);
        return;
    case 18:
        SetBentleyState(g_2dd5bc, 8, self);
        return;
    default:
        SetJmpBodyState(self, 4, 0);
        return;
    }
}
