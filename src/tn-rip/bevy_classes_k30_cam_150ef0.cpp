#include "cplcy.h"

extern "C" {
s128 bevy_classes_k30_cam_150780();
s128 bevy_classes_k30_cam_1507f8(K30CAM *);

void bevy_classes_k30_cam_150ef0(K30CAM *camera) {
    camera->position = bevy_classes_k30_cam_150780();
    camera->target = bevy_classes_k30_cam_1507f8(camera);
    f32 minimum = camera->minDistance;
    if (minimum >= 0.0f) {
        camera->distance = minimum;
    }
    camera->previousPosition = camera->currentPosition;
    camera->previousTarget = camera->currentTarget;
    camera->previousDistance = camera->currentDistance;
}

}
