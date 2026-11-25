#include "cm.h"
extern "C" {
extern CM B_002DDF40;
extern char B_003DD490;
s128 PosLoWorld(int);
int PpoSwFocus(char *);
s128 bevy_classes_k30_cam_150780(K30CAM *self) {
    s128 position;
    int target = self->field_0x10;
    if (target != 0) {
        position = PosLoWorld(target);
    } else {
        int focus = PpoSwFocus(&B_003DD490);
        if (focus != 0) {
            position = PosLoWorld(focus);
            ((float *)&position)[2] += 150.0f;
        } else {
            position = B_002DDF40.mat.row[3];
        }
    }
    return position;
}
}
