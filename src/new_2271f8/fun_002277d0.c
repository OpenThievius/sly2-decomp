/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "subtitle.h"

struct SW;
extern struct SW B_003DD490;

char *PchzStringFromId(struct SW *psw, s32 id);
char *strcpy(char *, const char *);

void func_002277D0(struct SUBTITLE *psubtitle, char *pchDestination) {
    s32 sid;

    sid = psubtitle->sid;
    if (sid == -1) {
        *pchDestination = 0;
        return;
    }
    strcpy(pchDestination, PchzStringFromId(&B_003DD490, sid));
}
