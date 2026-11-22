/* SPDX-License-Identifier: GPL-3.0-or-later */
#include "types.h"

struct BQ;
int sceScfGetLanguage();
void bevy_camera_follow_activity(void *, int, void *);
void func_001A2C20(int);
void func_001A2DA0(int);
void StartBootQueue(struct BQ *);
extern char B_002DEB30;
extern struct BQ B_002E1E88;

void func_001613A8(void) {
    func_001A2C20(0);
    func_001A2DA0(sceScfGetLanguage());
    bevy_camera_follow_activity(&B_002DEB30, 0, 0);
    StartBootQueue(&B_002E1E88);
}
