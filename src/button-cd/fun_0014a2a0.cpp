extern "C" {
int FGoalAnimDone(int);
int FGoalReactDone(int);
int GoalFollowCrv_FAtEnd(int);
int PpoSwFocusBase(void *);
int PsenseFindNotice(int, int, int);
int func_0014A478(char *);
int func_0014A4D0(char *);
int func_0014AA30(char *);
void func_0014AD70(char *);
void func_0014AE38(char *, int);
void func_001EEF98(char *);
int func_001EF0A8(char *);
int func_00209098(int);
extern char B_003DD490[];
}

void func_0014A2A0(char *self)
{
    int done;
    func_001EEF98(self);
    func_0014A4D0(self);
    while (func_001EF0A8(self) == 0) {
        unsigned int state = *(unsigned int *)(self + 0x30);
        switch (state) {
        case 0:
            if (func_00209098(*(int *)(self + 0x10)) != 0)
                goto busy;
            if (func_0014A478(self) != 0)
                goto reacted;
            {
                int result = func_0014AA30(self);
                *(int *)(self + 0x40) = result;
                if (result == *(int *)(self + 0x3C)) {
                    int notice = PsenseFindNotice(*(int *)(self + 0x10), PpoSwFocusBase(B_003DD490), 0);
                    *(int *)(self + 0x44) = notice;
                    if (notice != 0)
                        func_0014AE38(self, 3);
                } else {
                    func_0014AD70(self);
                }
            }
            break;
        case 1:
            if (func_00209098(*(int *)(self + 0x10)) != 0)
                goto busy;
            if (func_0014A478(self) != 0) {
            reacted:
                func_0014AE38(self, 2);
                break;
            }
            if (GoalFollowCrv_FAtEnd(*(int *)(self + 0x18)) != 0)
                goto idle;
            PsenseFindNotice(*(int *)(self + 0x10), PpoSwFocusBase(B_003DD490), 0);
            break;
        case 2:
            if (func_00209098(*(int *)(self + 0x10)) != 0)
                goto busy;
            done = FGoalAnimDone(*(int *)(self + 0x18));
            goto check;
        case 3:
            if (func_00209098(*(int *)(self + 0x10)) != 0) {
            busy:
                func_0014AE38(self, 4);
                break;
            }
            done = FGoalReactDone(*(int *)(self + 0x18));
        check:
            if (done != 0) {
            idle:
                func_0014AE38(self, 0);
            }
            break;
        case 4:
            if (func_00209098(*(int *)(self + 0x10)) == 0)
                func_0014AE38(self, 0);
            break;
        }
        if (state == *(unsigned int *)(self + 0x30))
            break;
    }
}
