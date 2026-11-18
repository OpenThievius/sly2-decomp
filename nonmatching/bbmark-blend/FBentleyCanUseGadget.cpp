struct SLOT_136870 { int pad0; int object; int active; };
struct TARGET_136870 { char pad0[0x15C]; int gadget; };
struct BENTLEY_136870 {
    char pad0[0x12F0];
    int hasBinoc;
    char pad12f4[0x13D0 - 0x12F4 - 0];
};
extern "C" {
int FActiveCplcy(void *);
int FAttachAllowsGadget(void *, int);
int FGadgetObjActive(int);
int FJmpAllowsGadget(void *, int);
int PleaseFindBest(int, int);
SLOT_136870 *PslotBentleyGadget(void *, int);
int bevy_player_p15_binoc_active();
int func_0019EEF0(void *, int);
extern char B_002DE2E0;
extern int g_2dfbc0;
int FBentleyCanUseGadget(char *self, int gadget) {
    int allowed;
    if (*(long *)(self + 0x1818) != 0) {
        return 0;
    }
    if (bevy_player_p15_binoc_active() != 0) {
        return 0;
    }
    switch (*(unsigned *)(self + 0x13D0)) {
    case 0: case 1: case 5: case 7:
        goto second;
    case 2:
        allowed = FJmpAllowsGadget(self + 0x2C0, gadget);
        break;
    case 3:
        allowed = FAttachAllowsGadget(self + 0x4C0, gadget);
        break;
    case 13:
        allowed = func_0019EEF0(self + 0xF50, gadget);
        break;
    case 12:
        goto twelve;
    default:
        goto ret0;
    }
    if (allowed != 0)
        goto second;
ret0:
    return 0;
twelve:
    if ((unsigned)(*(int *)(self + 0x11B4) - 4) < 3U) {
        switch (gadget) {
        case 4: case 7: case 9: case 11: case 13:
            if (((TARGET_136870 *)*(char **)(self + 0x11C0))->gadget != gadget)
                goto ret0;
            return 1;
        }
    }
    return 0;
second:
    switch (gadget) {
    case 4: case 5: case 7: case 9: case 11: case 13: {
        SLOT_136870 *slot = PslotBentleyGadget(self, gadget);
        if (slot->active != 0) {
            if (FGadgetObjActive(slot->active) == 0)
                goto ret0;
            return 1;
        }
        if (slot->object == 0)
            goto ret0;
        if (PleaseFindBest(slot->object, 2) != 0)
            return 1;
        goto ret0;
    }
    case 3: {
        int result = 0;
        if (*(int *)(self + 0x12F0) != 0) {
            if ((g_2dfbc0 & 2) != 0)
                result = FActiveCplcy(&B_002DE2E0) == 0;
        }
        return result;
    }
    case 1: case 2: case 8: case 10: case 12: case 14:
        return 1;
    default:
        goto ret0;
    }
}
}
