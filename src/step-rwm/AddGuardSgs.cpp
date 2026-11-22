// SPDX-License-Identifier: GPL-3.0-or-later
#include "sly2.h"
#include "stepguard.h"
struct ENTRY { int sgs; int activity; };
extern "C" {
void SetGuardGrfsgs(STEPGUARD *, unsigned long);
int FIsSgsInGrfsgs(unsigned long, int);
unsigned long GrfsgsFromSgs(int);
void bevy_camera_follow_activity(void *, int, STEPGUARD *);
extern char B_002DEB30[];
extern ENTRY D_002C3D98[];
}
extern "C" void AddGuardSgs(STEPGUARD *pguard, int sgs)
{
    unsigned long grfNew = GrfsgsFromSgs(sgs);
    SetGuardGrfsgs(pguard, pguard->grfsgs | grfNew);
    int sgsNone = -1;
    int *argv[2];
    argv[0] = &sgs;
    argv[1] = &sgsNone;
    pguard->HandleSpliceEvent(7, 0, 2, (int)argv, 0);
    for (unsigned index = 0; index < 2; index++) {
        if (FIsSgsInGrfsgs(grfNew, D_002C3D98[index].sgs))
            bevy_camera_follow_activity(B_002DEB30, D_002C3D98[index].activity, pguard);
    }
}
