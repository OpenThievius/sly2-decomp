/* SPDX-License-Identifier: GPL-3.0-or-later */
/* MATRIX3Q, a rotation matrix held as three quadword rows (copied with lq/sq): func_00209840 copies one into the actor's heading
   (STEP::matHeading, step.h), SetStepRadTarget builds one there, GoalJump_Activate builds one in its goal (guard.h). C and C++. */
#ifndef SLY2_MATRIX3Q_H
#define SLY2_MATRIX3Q_H
#include "types.h"

struct MATRIX3Q {
    QW row[3];
};
#endif
